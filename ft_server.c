/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_server.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/14 15:06:18 by macbook       #+#    #+#                 */
/*   Updated: 2023/02/21 18:01:54 by cbijman       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./include/libft.h"
#include "./include/minitalk.h"


//Signals hebben geen wachtrij. 5 clients die bytes versturen kan een wissel veroorzaken waardoor bytes & bits worden omgewisseld.


void	sighook(int signal, siginfo_t *info, void *context)
{
	static int		bits = 0;
	static char		byte = 0;
	static pid_t	pid;

	(void) context;
	if (!pid)
		pid = info -> si_pid;
	if (signal == SIGUSR1)
		byte += (1 << bits);
	bits++;
	if (bits == 8)
	{
		bits = 0;
		ft_putchar(byte);
		byte = 0;
	}
}

int	main(void)
{
	struct sigaction	action;

	ft_printf("%sPID: %s%d\n", GRAY, RESET, getpid());
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = sighook;
	sigaction(SIGUSR1, &action, 0);
	sigaction(SIGUSR2, &action, 0);
	while (1);
	return (0);
}
