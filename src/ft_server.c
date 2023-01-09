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
		printf("%c", i);
		i = 0;
		bit = 0;
	}
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
	//struct sigaction *action;
	ft_printf("%sPID: %s%d\n", GRAY, RESET, getpid());
	hook(getpid());
	return (0);
}
