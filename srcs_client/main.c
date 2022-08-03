/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:26:05 by tnoulens          #+#    #+#             */
/*   Updated: 2022/08/03 15:41:46 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static int	delivery_confirmation(int num)
{
	(void)num;
	write(1, BLUE"\nmessage has been received indeed!\n"END, 13);
	exit(EXIT_SUCCESS);
}

static int	bit_sender(pid_t the_pid, unsigned char uc)
{
	unsigned char	bit_comp;

	bit_comp = 1 << CHAR_BIT;
	while (bit_comp)
	{
		if (bit_comp & uc)
		{
			if (kill(the_pid, SIGUSR1) == -1)
				return (0);
		}
		else
			if (kill(the_pid, SIGUSR2) == -1)
				return (0);
		bit_comp >>= 1;
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
	while (argv[2])
	{
		bit_sender(the_pid, (unsigned char)*argv[2]);
		++*argv;
		usleep(1000);
	}
	sleep(5);
	signal(SIGUSR1, delivery_confirmation);
	return (0);
}
