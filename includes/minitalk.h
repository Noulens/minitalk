/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:51:46 by tnoulens          #+#    #+#             */
/*   Updated: 2022/08/04 20:36:29 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 199309L
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include <limits.h>
# include "../libft/libft.h"

/* Define */
# define BUFF 5100

/* Structure */
typedef struct s_data
{
	pid_t	the_pid;
	char	buf[BUFF];
}	t_data;

/* This is a minimal set of ANSI/VT100 color codes */
# define END "\033[0m"
# define GREY "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"

/* Proto */

#endif
