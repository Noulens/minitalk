/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:26:05 by tnoulens          #+#    #+#             */
/*   Updated: 2022/08/05 14:33:17 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	g_tmp;

static void	tmp_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR2)
		g_tmp = 0;
	else if (sig == SIGUSR1)
	{
		ft_printf(BLUE"message has been received indeed! ☑️ \n"END);
		exit(EXIT_SUCCESS);
	}
}

static void	bit_sender(pid_t the_pid, char c)
{
	int	bit_comp;

	g_tmp = 1;
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
		while (g_tmp)
		{
		}
		g_tmp = 1;
	}
}

int	main(int argc, char **argv)
{
	pid_t				the_pid;
	struct sigaction	sa;

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = tmp_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (argc != 3)
		return (ft_printf(RED"wrong number of argument\n"END), 1);
	the_pid = ft_atoi(argv[1]);
	if (the_pid == 0)
		return (ft_printf(RED"try server's PID please\n"END), 1);
	while (*argv[2])
	{
		bit_sender(the_pid, *argv[2]);
		++argv[2];
	}
	bit_sender(the_pid, '\0');
	g_tmp = 0;
	return (0);
}
