/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_client.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 12:07:01 by macbook       #+#    #+#                 */
/*   Updated: 2023/02/22 17:38:28 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"

void	validate_response(int sig)
{
	if (sig != SIGUSR1)
		return ;
	ft_printf("%sMessage received\n", GRAY);
}

void	send_bits(pid_t pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (1 << bit)) >= 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(300);
		bit++;
		signal(SIGUSR1, validate_response);
	}
}

void	send_string(pid_t pid, const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		send_bits(pid, str[i]);
	//send_bits(pid, '\n');
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;

	if (argc < 3)
		return (ft_putstr("Error\n"), 1);
	server_pid = ft_atoi(argv[1]);
	send_string(server_pid, argv[2]);
	return (0);
}
