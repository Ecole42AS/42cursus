#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <netinet/ip.h>

int client_count = 0, max_fd = 0;
int client_ids[65536];

char *client_msgs[65536];

fd_set read_set, write_set, active_set;

char buf_in[1001], buf_out[42];

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

void fatal_error()
{
    write(2, "Fatal error", 11);
    exit(1);
}

void broadcast(int sender, char *msg)
{
    for (int fd = 0; fd <= max_fd; fd++)
    {
        if (FD_ISSET(fd, &write_set) && fd != sender)
            send(fd, msg, strlen(msg), 0);
    }
}

void add_client(int fd)
{
    max_fd = fd > max_fd ? fd : max_fd;
    client_ids[fd] = client_count++;
    client_msgs[fd] = NULL;
    FD_SET(fd, &active_set);
    sprintf(buf_out, "server: client %d just arrived\n", client_ids[fd]);
    broadcast(fd, buf_out);
}

void remove_client(int fd)
{
    sprintf(buf_out, "Server: client %d just left\n", client_ids[fd]);
    broadcast(fd, buf_out);
    free(client_msgs[fd]);
    FD_CLR(fd, &active_set);
    close(fd);
}


void traiter_messages(int fd)
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

int create_socket()
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
    int sock_fd = create_socket();

    struct sockaddr_in servaddr;
	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433);
	servaddr.sin_port = htons(atoi(av[1])); // replace 8080

	if (bind(sock_fd, (const struct sockaddr *)&servaddr, sizeof(servaddr)))
		fatal_error();
	if (listen(sock_fd, SOMAXCONN)) // the main uses 10, SOMAXCONN is 180 on my machine
		fatal_error();

    while (1)
    {
        read_set = write_set = active_set;

        if (select(max_fd + 1, &read_set, &write_set, NULL, NULL) < 0)
            fatal_error();

        for (int fd = 0; fd <= max_fd; fd++)
        {
            if (!FD_ISSET(fd, &read_set))
                continue;

            if (fd == sock_fd)
            {
                socklen_t addr_len = sizeof(servaddr);
                int client_fd = accept(sock_fd, (struct sockaddr *)&servaddr, &addr_len);
                if (client_fd >= 0)
                {
                    add_client(client_fd);
                    break;
                }
            }
            else
            {
                int read_bytes = recv(fd, buf_in, 1000, 0);
                if (read_bytes <= 0)
                {
                    remove_client(fd);
                    break;
                }
                buf_in[read_bytes] = '\0';
                client_msgs[fd] = str_join(client_msgs[fd], buf_in);
                traiter_messages(fd);
            }
        }
    }
    return (0);
}







