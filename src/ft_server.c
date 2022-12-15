/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_server.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cbijman <cbijman@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 15:35:21 by cbijman       #+#    #+#                 */
/*   Updated: 2022/12/15 18:54:40 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"

#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void	handler(int signal)
{
	static int bit;
	static int i;
	if (signal == SIGUSR1)
		i |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		bit = 0;
		i = 0;
	}
	//ft_printf("Bit: %d\tI: %d", bit, i);
}

int	hook(int pid)
{
	ft_printf("%sStatus: %sWaiting for incoming messages...\n", GRAY, RESET);
	while (pid != 0)
	{
		signal(SIGUSR1, handler);
		signal(SIGUSR2, handler);
		pause();
	}
	return (0);
}

int	main(void)
{
	ft_printf("%sPID: %s%d\n", GRAY, RESET, getpid());
	hook(getpid());
	return (0);
}
