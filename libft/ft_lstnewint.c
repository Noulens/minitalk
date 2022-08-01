/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnewint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnoulens <tnoulens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:35:24 by tnoulens          #+#    #+#             */
/*   Updated: 2022/06/23 19:32:43 by tnoulens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_int	*ft_lstnewint(int content)
{
	t_int	*first;

	first = (t_int *)malloc(sizeof(t_int));
	if (!first)
		return (NULL);
	first->digit = content;
	first->next = NULL;
	return (first);
}
