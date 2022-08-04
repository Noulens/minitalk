/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:26:05 by tnoulens          #+#    #+#             */
/*   Updated: 2022/08/04 20:05:29 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	delivery_confirmation(int num)
{
	(void)num;
	write(1, BLUE"\nmessage has been received indeed!\n"END, 13);
	exit(EXIT_SUCCESS);
}

static void	bit_sender(pid_t the_pid, char c)
{
	int	bit_comp;

	bit_comp = 0b10000000;
	while (bit_comp)
	{
		if (bit_comp & c)
		{
			if (kill(the_pid, SIGUSR1) == -1)
				return ;
		}
		else
			if (kill(the_pid, SIGUSR2) == -1)
				return ;
		bit_comp >>= 1;
		usleep(1000);
	}
}

int	main(int argc, char **argv)
{
	pid_t	the_pid;

	if (argc != 3)
		return (ft_printf(RED"\nwrong number of argument\n"END), 1);
	the_pid = ft_atoi(argv[1]);
	if (the_pid == 0)
		return (ft_printf(RED"\ntry server's PID please\n"END), 1);
	while (*argv[2])
	{
		bit_sender(the_pid, *argv[2]);
		++argv[2];
	}
	bit_sender(the_pid, '\0');
	signal(SIGUSR1, delivery_confirmation);
	return (0);
}
