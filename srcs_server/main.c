/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:50:17 by tnoulens          #+#    #+#             */
/*   Updated: 2022/08/03 18:03:49 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

t_string	g_info;

static void	handler0(int num)
{
	(void)num;
	
	write(1, RED"\nI won't die\n"END, 24);
}

static void	handler1(int num)
{
	(void)num;
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

int	main(int argc, char **argv)
{
	pid_t	the_pid;

	(void)argv;
	if (argc != 1)
		return (ft_printf(RED"\nwrong number of argument\n"END), 1);
	the_pid = getpid();
	signal(SIGUSR1, handler0);
	signal(SIGUSR2, handler1);
	printf(YELLOW"Server ready, PID: %d\n"END, the_pid);
	while (1)
		pause();
}

/*
	on veut 'a' soit 97 ou 0b001100001
    
	int bit = 0b100000000; soit 256 en decimal, le max de unsigned char + 1
    unsigned char c = 0b0; on demarre c a 0
    
	on recoit le signal 001100001
	on incremente l'index quand on recoit un 0 mais on ne fait rien d'autre
    
	on fait un bitshift de la taille de l'index quand on recoit un 1

	c est dans une variable struct globale
	
    c  += bit >> 2; 000000000 001000000|00 -> 001000000 DECIMAL: 64
    c  += bit >> 3; 001000000 000100000|000 -> 001100000 DECIMAL: 32
    c  += bit >> 8; 001100000 000000001|00000000 -> 001100001 DECIMAL: 1

	64 + 32  + 1 = 97 = 'a'
	
	dans ce cas, += est equivalent a |=
*/
