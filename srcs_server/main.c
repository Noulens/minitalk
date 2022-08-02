/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:50:17 by tnoulens          #+#    #+#             */
/*   Updated: 2022/08/02 19:01:16 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	handler(int num)
{
	(void)num;
	write(1, RED"\nI won't die\n"END, 24);
}

int	main(int argc, char **argv)
{
	pid_t	the_pid;

	(void)argv;
	if (argc != 1)
		return (1);
	the_pid = getpid();
	signal(SIGUSR1, handler);
	printf(YELLOW"Server ready, PID: %d\n"END, the_pid);
	while (1)
		pause();
}
