/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/14 15:06:18 by macbook       #+#    #+#                 */
/*   Updated: 2023/02/22 17:46:24 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"

void	sighook(int signal, siginfo_t *info, void *context)
{
	static int		bits = 0;
	static char		byte = 0;

	(void) context;
	(void) info;
	if (signal == SIGUSR1)
		byte += (1 << bits);
	bits++;
	if (bits == 8)
	{
		ft_putchar(byte);
		bits = 0;
		byte = 0;
	}
}

int	main(void)
{
	struct sigaction	action;

	ft_printf("pid %d\n", getpid());
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = sighook;
	while (1)
	{
		sigaction(SIGUSR1, &action, 0);
		sigaction(SIGUSR2, &action, 0);
		usleep(100);
	}
	return (0);
}
