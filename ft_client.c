/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_client.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: macbook <macbook@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 12:07:01 by macbook       #+#    #+#                 */
/*   Updated: 2023/02/17 13:33:25 by macbook       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk.h"

char	*mt_strjoin(char *s1, char *s2, bool use_space)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 2, sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	if (use_space)
		str[i++] = ' ';
	str[i] = '\0';
	return (free(s1), str);
}

char	*copy_arguments_to_string(char **argv)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_calloc(1, 1);
	while (argv[i])
	{
		str = mt_strjoin(str, argv[i], argv[i + 1] != NULL);
		i++;
	}
	return (str);
}

void	send_bits(pid_t pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

void	send_string(pid_t pid, const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_bits(pid, str[i]);
		i++;
	}
	ft_printf("Length: %d\n", ft_strlen(str));
	send_bits(pid, '\n');
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*text;

	if (argc < 3)
		return (ft_putstr("Error\n"), 1);
	server_pid = ft_atoi(argv[1]);
	if (argc >= 4)
		text = copy_arguments_to_string(&argv[2]);
	else
		text = ft_strdup(argv[2]);
	if (!text)
		return (ft_putstr("Error\n"), 1);
	send_string(server_pid, text);
	return (free(text), 0);
}
