/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 16:57:41 by mmoreira          #+#    #+#             */
/*   Updated: 2021/07/12 19:56:33 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static size_t	str_len(char *s)
{
	size_t	i;

	i = 0;
	if (!(s))
		return (i);
	while (*(s + i) != '\0')
		i++;
	return (i);
}

static char	*addchar(char *str, char c)
{
	char	*temp;
	int		i;

	temp = malloc((str_len(str) + 2) * sizeof(char));
	if (!(temp))
	{
		if (str)
			free(str);
		return (NULL);
	}
	if (!(str))
	{
		*(temp) = c;
		*(temp + 1) = '\0';
		return (temp);
	}
	i = -1;
	while (*(str + ++i))
		*(temp + i) = *(str + i);
	*(temp + i) = c;
	*(temp + i + 1) = '\0';
	free(str);
	return (temp);
}

static void	receiver(int sig, siginfo_t *info, void *ucontext)
{
	static int	c;
	static int	p;
	static char	*str;

	(void)ucontext;
	if (sig == SIGUSR2)
		c += 1 << (7 - p);
	if (++p == 8)
	{
		if (c)
			str = addchar(str, c);
		else
		{
			write(1, "/----------------------------------------\n| ", 44);
			write(1, str, str_len(str));
			write(1, "\n\\----------------------------------------\n\n", 44);
			free(str);
			str = NULL;
			kill(info->si_pid, SIGUSR1);
		}
		c = 0;
		p = 0;
	}
}

static void	print_pid(int n)
{
	int	num;
	int	pot;

	num = n;
	pot = 1;
	while (num >= 10)
	{
		num /= 10;
		pot *= 10;
	}
	write(1, "PID do server: ", 15);
	while (pot > 0)
	{
		num = (n / pot) + '0';
		write(1, &num, 1);
		n = n % pot;
		pot /= 10;
	}
	write(1, "\n\n", 2);
}

int	main(void)
{
	struct sigaction	newact;

	newact.sa_flags = SA_SIGINFO;
	newact.sa_sigaction = receiver;
	if (sigemptyset(&newact.sa_mask) == -1
		|| sigaction(SIGUSR1, &newact, NULL) == -1
		|| sigaction(SIGUSR2, &newact, NULL) == -1)
		return (1);
	print_pid(getpid());
	while (1)
		pause();
	return (0);
}
