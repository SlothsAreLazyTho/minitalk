/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_server.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/14 15:06:18 by macbook       #+#    #+#                 */
/*   Updated: 2023/02/17 13:33:52 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"

void	sighook(int signal, siginfo_t *info, void *context)
{
	static unsigned int	bits;
	static pid_t		pid;
	static char			byte;

	(void) context;
	if (!pid)
		pid = info -> si_pid;
	if (signal == SIGUSR1)
		byte |= (0x01 << bits);
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

	ft_printf("%sPID: %s%d\n", GRAY, RESET, getpid());
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = sighook;
	sigaction(SIGUSR1, &action, 0);
	sigaction(SIGUSR2, &action, 0);
	while (1)
		pause();
	return (0);
}
