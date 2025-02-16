#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/ip.h>

// Variables globales renommées pour plus de clarté
int client_count = 0, max_fd = 0;
int client_ids[65536];
char *client_msgs[65536];

fd_set read_set, write_set, active_set;
char buf_in[1024], buf_out[42];


// START COPY-PASTE FROM GIVEN MAIN

int extract_message(char **buf, char **msg)
{
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i])
	{
		if ((*buf)[i] == '\n')
		{
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

// END COPY-PASTE


// Fonction appelée en cas d'erreur fatale
void fatal_error()
{
	write(2, "Fatal error\n", 12);
	exit(1);
}

// Envoie un message à tous les clients sauf l'émetteur
void broadcast(int sender, char *msg)
{
	for (int fd = 0; fd <= max_fd; fd++)
	{
		if (FD_ISSET(fd, &write_set) && fd != sender)
			send(fd, msg, strlen(msg), 0);
	}
}

// Ajoute un nouveau client et notifie les autres
void add_client(int fd)
{
	max_fd = fd > max_fd ? fd : max_fd;
	client_ids[fd] = client_count++;
	client_msgs[fd] = NULL;
	FD_SET(fd, &active_set);
	sprintf(buf_out, "server: client %d just arrived\n", client_ids[fd]);
	broadcast(fd, buf_out);
}

// Supprime un client (fermeture de socket, libération de mémoire) et notifie les autres
void remove_client(int fd)
{
	sprintf(buf_out, "server: client %d just left\n", client_ids[fd]);
	broadcast(fd, buf_out);
	free(client_msgs[fd]);
	FD_CLR(fd, &active_set);
	close(fd);
}

// Traite les messages reçus sur la socket d'un client et les diffuse
void send_msg(int fd)
{
	char *msg;

	while (extract_message(&(client_msgs[fd]), &msg))
	{
		sprintf(buf_out, "client %d: ", client_ids[fd]);
		broadcast(fd, buf_out);
		broadcast(fd, msg);
		free(msg);
	}
}

// Crée la socket serveur et l'ajoute aux sockets actives
int creer_socket()
{
	max_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (max_fd < 0)
		fatal_error();
	FD_SET(max_fd, &active_set);
	return max_fd;
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}

	FD_ZERO(&active_set);
	int sock_fd = creer_socket();

	// START COPY-PASTE FROM MAIN

	struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433);
	servaddr.sin_port = htons(atoi(av[1])); // replace 8080

	if (bind(sock_fd, (const struct sockaddr *)&servaddr, sizeof(servaddr)))
		fatal_error();
	if (listen(sock_fd, SOMAXCONN)) // the main uses 10, SOMAXCONN is 180 on my machine
		fatal_error();

	// END COPY-PASTE

	while (1)
	{
		// Préparation des ensembles de sockets pour select
		read_set = write_set = active_set;

		if (select(max_fd + 1, &read_set, &write_set, NULL, NULL) < 0)
			fatal_error();

		// Parcourt toutes les sockets pour voir celles actives
		for (int fd = 0; fd <= max_fd; fd++)
		{
			if (!FD_ISSET(fd, &read_set))
				continue;

			if (fd == sock_fd)
			{
				// Acceptation d'un nouveau client
				socklen_t addr_len = sizeof(servaddr);
				int client_fd = accept(sock_fd, (struct sockaddr *)&servaddr, &addr_len);
				if (client_fd >= 0)
				{
					add_client(client_fd);
					break ;
				}
			}
			else
			{
				// Réception de données d'un client
				int read_bytes = recv(fd, buf_in, 1000, 0);
				if (read_bytes <= 0)
				{
					remove_client(fd);
					break ;
				}
				buf_in[read_bytes] = '\0';
				client_msgs[fd] = str_join(client_msgs[fd], buf_in);
				send_msg(fd);
			}
		}
	}
	return 0;
}
