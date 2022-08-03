/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:50:17 by tnoulens          #+#    #+#             */
/*   Updated: 2022/08/03 20:30:25 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_data	g_info;

static void	initialize(t_data *g_info)
{
	g_info->index = 0;
	g_info->c = 0b0;
	g_info->p = NULL;
	g_info->buf[0] = 0;
	g_info->i = 0;
}

static char	*ft_append(char *old, char *new)
{
	int		len;
	char	*ptr;
	char	*ret;
	char	*oldptr;

	if ((old == NULL && new == NULL) || new == NULL)
		return (NULL);
	oldptr = old;
	if (!old)
		len = ft_strlenb(new);
	else
		len = ft_strlenb(oldptr) + ft_strlenb(new);
	ret = (char *)malloc(len * sizeof(char) + 1);
	if (!ret)
		return (NULL);
	ret[0] = 0;
	ptr = ret;
	while (oldptr && *oldptr)
		*ptr++ = *oldptr++;
	while (*new)
		*ptr++ = *new++;
	*ptr = 0;
	free(old);
	return (ret);
}

void	handler0(int num)
{
	(void)num;
	g_info.index += 1;
	if (g_info.index == 9)
	{
		g_info.buf[g_info.i] = g_info.c;
		if (g_info.c == '\0')
			return (ft_printf("%s%s", g_info.p, g_info.buf), (void)0);
		++g_info.i;
		g_info.index = 0;
		g_info.c = 0b0;
		if (g_info.i == BUFF)
		{
			g_info.p = ft_append(g_info.p, g_info.buf);
			g_info.i = 0;
		}
	}
}

void	handler1(int num)
{
	int	bit;

	(void)num;
	bit = 0b100000000;
	if (g_info.index == 9)
	{
		g_info.buf[g_info.i] = g_info.c;
		if (g_info.c == '\0')
			return (ft_printf("%s%s", g_info.p, g_info.buf), (void)0);
		++g_info.i;
		g_info.index = 0;
		g_info.c = 0b0;
		if (g_info.i == BUFF)
		{
			g_info.p = ft_append(g_info.p, g_info.buf);
			g_info.i = 0;
		}
		return ;
	}
	g_info.c |= (bit >> g_info.index);
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
	while (1)
		pause();
	signal(SIGUSR1, handler1);
	signal(SIGUSR2, handler0);
}

/*
	on veut 'a' soit 97 ou 0b001100001
    
	int bit = 0b100000000; soit 256 en decimal, le max de unsigned char + 1
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

	on stocke c dans un buffer qui est aussi dans la struct, si le buffer est
	plein on fait ft_append	on reinitialise c et le buffer pour le prochain
	char.
	
	a la fin on free si on a utilise ft_append
*/
