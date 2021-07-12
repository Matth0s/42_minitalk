/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoreira <mmoreira@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:39:03 by mmoreira          #+#    #+#             */
/*   Updated: 2021/07/12 16:00:22 by mmoreira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	provider(int c, int pid)
{
	int	p;

	p = 8;
	while (p--)
	{
		if (!(c & 1 << p))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
	}
}

static int	get_pid(char *str, int *pid)
{
	int	i;

	i = 0;
	while (*(str + i))
	{
		if (*(str + i) >= 48 && *(str + i) <= 57)
			*pid = (*pid * 10) + (*(str + i) - '0');
		else
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	int		pid;

	pid = 0;
	if (argc != 3)
	{
		write(1, "Conserta o numero de argumentos ai tio", 38);
		return (0);
	}
	i = get_pid(*(argv + 1), &pid);
	if (i)
	{
		write(1, "Esse PID ai ta meio estranho meu cria", 37);
		return (0);
	}
	while (*(*(argv + 2) + i))
		provider(*(*(argv + 2) + i++), pid);
	provider(0, pid);
	return (0);
}
