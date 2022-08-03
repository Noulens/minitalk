/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:50:17 by tnoulens          #+#    #+#             */
/*   Updated: 2022/08/03 12:31:45 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	handler0(int num)
{
	(void)num;
	write(1, RED"\nI won't die\n"END, 24);
}

static char	*ft_append(char *old, char *new)
{
	int				len;
	register char	*ptr;
	char			*ret;
	register char	*oldptr;

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
	printf(YELLOW"Server ready, PID: %d\n"END, the_pid);
	while (1)
		pause();
}
