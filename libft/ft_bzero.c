/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:53:51 by tnoulens          #+#    #+#             */
/*   Updated: 2022/05/10 13:53:28 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = s;
	while (n--)
		*ptr++ = '\0';
	return (s);
}

/*#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
    char	dest[10];

    ft_bzero(dest, 5);
	printf("5 0's: %s", dest);
	return (0);
}*/
