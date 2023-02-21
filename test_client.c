/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test_client.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ajordan- <ajordan-@student.42urduliz.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 16:19:55 by ajordan-      #+#    #+#                 */
/*   Updated: 2023/02/20 17:55:19 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void	ft_send_bits(int pid, char i)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((i & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(300);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			ft_send_bits(pid, argv[2][i]);
			i++;
		}
		ft_send_bits(pid, '\n');
	}
	else
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		ft_printf("\033[33mTry: ./client <PID> <MESSAGE>\033[0m\n");
		return (1);
	}
	return (0);
}
