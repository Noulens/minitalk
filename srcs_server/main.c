/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:50:17 by tnoulens          #+#    #+#             */
/*   Updated: 2022/08/04 19:24:00 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_data	g_info;

static void	initializer(char *buf)
{
	int	i;

	i = 0;
	while (i < BUFF - 1)
	{
		buf[i] = 0;
		i++;
	}
}

static void	initialize(t_data *g_info)
{
	initializer(g_info->buf);
}

void	handler(int	num)
{
	static int				index;
	static unsigned char 	c;
	static int				i;
	
	if (num == SIGUSR1)
		c |= 0b10000000 >> index++;
	else if (num == SIGUSR2)
		index++;
	if (index == 8)
	{
		g_info.buf[i] = c;
		++i;
		if (c == '\0')
		{
			i = 0;
			ft_printf("%s", g_info.buf);
			initializer(g_info.buf);
		}
		index = 0;
		c = 0b0;
	}
}

int	main(int argc, char **argv)
{
	pid_t	the_pid;

	(void)argv;
	(void)argc;
	if (argc != 1)
		return (ft_printf(RED"\nwrong number of argument\n"END), 1);
	the_pid = getpid();
	initialize(&g_info);
	printf(YELLOW" 🤙 Server ready 📲, PID: %d\n"END, the_pid);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
	{
		pause();
	}
}
/*
	if (g_info.index == 8)
	{
		g_info.buf[g_info.i] = g_info.c;
		if (g_info.c == '\0')
			ft_putstr_fd(g_info.buf, 0);
		++g_info.i;
		g_info.index = 0;
		g_info.c = 0b0;
		if (g_info.i == BUFF)
		{
			g_info.p = ft_append(g_info.p, g_info.buf);
			g_info.i = 0;
		}
	}
*/
/*
	on veut 'a' soit 97 ou 0b001100001
    
	int bit = 0b10000000; soit 128 en decimal, le max de unsigned char + 1
    unsigned char c = 0b0; on demarre c a 0
    
	on recoit le signal 001100001
	
	dans la fonction qui gere les 0, on incremente l'index quand on recoit
	un 0 (SIGUSR1) mais on ne fait rien d'autre
    
	dans la fonction qui gere les 1, on fait un bitshift de la taille de
	l'index quand on recoit un 1 (SIGUSR2)

	c et index sont dans une variable struct globale
	
    c  += bit >> 2; 000000000 001000000|00 -> 001000000 DECIMAL: 64
    c  += bit >> 3; 001000000 000100000|000 -> 001100000 DECIMAL: 32
    c  += bit >> 8; 001100000 000000001|00000000 -> 001100001 DECIMAL: 1

	64 + 32  + 1 = 97 = 'a'
	
	dans ce cas, "+=" est equivalent a "|=" :
	
	c  |= bit >> 2;
	c  |= bit >> 3;
	c  |= bit >> 8;

	on stocke c dans un buffer qui est aussi dans la struct
*/
