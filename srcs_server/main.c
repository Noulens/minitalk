/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:50:17 by tnoulens          #+#    #+#             */
/*   Updated: 2022/08/05 15:34:56 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_data	g_info;

static void	initialize(t_data *g_info)
{
	int	i;

	i = 0;
	while (i < BUFF - 1)
	{
		g_info->buf[i] = 0;
		i++;
	}
}

static void	handler(int sig, siginfo_t *info, void *context)
{
	static int				index;
	static unsigned char	c;
	static int				i;

	(void)context;
	if (sig == SIGUSR1)
		c |= 0b10000000 >> index++;
	if (sig == SIGUSR2)
		index++;
	if (index == 8)
	{
		g_info.buf[i] = c;
		++i;
		if (c == '\0')
		{
			i = 0;
			ft_printf(END"%s\n"END, g_info.buf);
			kill(info->si_pid, SIGUSR1);
			initialize(&g_info);
		}
		index = 0;
		c = 0b0;
	}
	kill(info->si_pid, SIGUSR2);
}

int	main(int argc, char **argv)
{
	pid_t				pid_server;
	struct sigaction	sa;

	(void)argv;
	(void)argc;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (argc != 1)
		return (ft_printf(RED"wrong number of argument\n"END), 1);
	pid_server = getpid();
	initialize(&g_info);
	printf(YELLOW" 🤙 Server ready 📲, PID: %d\n"END, pid_server);
	while (42)
		pause();
}

/*
	on veut 'a' soit 97 ou 0b001100001
    
	int bit = 0b10000000; soit 128 en decimal, le max de char + 1
    unsigned char c = 0b0; on demarre c a 0
    
	on recoit le signal 001100001
	
	dans la fonction qui gere les 0, on incremente l'index quand on recoit
	un 0 (SIGUSR1), on fait un bitshift et on incremente index pour le cas SIGUSR2
    
	dans la fonction qui gere les 1, on fait un bitshift de la taille de
	l'index quand on recoit un 1 (SIGUSR2)

	c est dans une variable struct globale
	
    c  += bit >> 2; 000000000 001000000|00 -> 001000000 DECIMAL: 64
    c  += bit >> 3; 001000000 000100000|000 -> 001100000 DECIMAL: 32
    c  += bit >> 8; 001100000 000000001|00000000 -> 001100001 DECIMAL: 1

	64 + 32  + 1 = 97 = 'a'
	
	dans ce cas, "+=" est equivalent a "|=" :
	
	c  |= bit >> 2;
	c  |= bit >> 3;
	c  |= bit >> 8;

	on stocke c dans le buffer qui est dans la struct globale
*/
