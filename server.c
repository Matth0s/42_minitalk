/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:26:49 by mmoreira          #+#    #+#             */
/*   Updated: 2021/07/12 14:18:43 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <sys/siginfo.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	print_pid(int n)
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
	write(1,"PID do server: ",15);
	while (pot > 0)
	{
		num = (n / pot) + '0';
		write(1, &num, 1);
		n = n % pot;
		pot /= 10;
	}
	write(1, "\n\n", 2);
}

size_t	str_len(char *s)
{
	size_t	i;

	i = 0;
	if (!(s))
		return (i);
	while (*(s + i) != '\0')
		i++;
	return (i);
}

char	*addchar(char *str, char c)
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

void	receiver(int sig)
{
	static int	c;
	static int	p;
	static char	*str;

	if (sig == SIGUSR2)
		c += 1 << (7 - p);
	if (++p == 8)
	{
		if (c)
			str = addchar(str, c);
		else
		{
			write(1, str, str_len(str));
			write(1, "\n", 1);
			free(str);
			str = NULL;
		}
		c = 0;
		p = 0;
	}
}

/*
void	receiver_I(int sig, siginfo_t *info, void *ucontext)
{
	static int	c;
	static int	p;
	static char	*str;

	(void)info;
	(void)ucontext;

	if (sig == SIGUSR2)
		c += 1 << (7 - p);
	if (++p == 8)
	{
		if (c)
			str = addchar(str, c);
		else
		{
			write(1, str, str_len(str));
			write(1, "\n", 1);
			free(str);
			str = NULL;
		}
		c = 0;
		p = 0;
	}
}
 */

int	main(void)
{
	struct sigaction	newact;

	newact.sa_handler = receiver;
	newact.sa_flags = 0;
	if (sigemptyset(&newact.sa_mask) == -1
		|| sigaction(SIGUSR1, &newact, NULL) == -1
		|| sigaction(SIGUSR2, &newact, NULL) == -1)
		return (1);

/* 	newact.sa_flags = SA_SIGINFO;
	newact.sa_sigaction = receiver_I;
	if (sigemptyset(&newact.sa_mask) == -1
		|| sigaction(SIGUSR1, &newact, NULL) == -1
		|| sigaction(SIGUSR2, &newact, NULL) == -1)
		return (1); */

/* 	signal(SIGUSR1, receiver);
	signal(SIGUSR2, receiver); */
	print_pid(getpid());
	while (1)
		pause();
	return (0);
}
