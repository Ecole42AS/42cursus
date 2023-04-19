#include "ft_printf/includes/ft_printf.h"
#include "minitalk.h"

void	send_bit(int pid, char c)
{
	int	shift;

	shift = 0;
	while (shift < 8)
	{
		if ((c >> shift) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		shift++;
		usleep(100);
	}
}

void	ft_send_str(int pid, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		send_bit(pid, str[i]);
		i++;
	}
	send_bit(pid, '\0');
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*str;

	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		str = argv[2];
		ft_send_str(pid, str);
	}
	else
		ft_printf("\nYOU EITHER LEFT IT BLANK OR ARE DOING MORE THAN 1 WORD\n\n");
	return (0);
}
