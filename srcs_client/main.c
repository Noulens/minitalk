/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:26:05 by tnoulens          #+#    #+#             */
/*   Updated: 2022/08/02 19:00:27 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	delivery_confirmation(int num)
{
	(void)num;
	write(1, BLUE"\nmessage has been received indeed\n"END, 13);
}

int	bit_sender(pid_t the_pid, unsigned char uc)
{
	unsigned char	bit_comp;

	bit_comp = 1 << CHAR_BIT;
	while (bit_comp)
	{
		if(bit_comp & uc)
			if(kill(the_pid, SIGUSR1) == -1)
				return(0);
		else
			if (kill(the_pid, SIGUSR2) == -1)
				return(0);
		bit_comp >>= 1;
	}
}

int	main(int argc, char **argv)
{
	;
}
