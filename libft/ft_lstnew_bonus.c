/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:35:24 by tnoulens          #+#    #+#             */
/*   Updated: 2022/06/26 09:53:36 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_int	*ft_lstnew(char *content)
{
	t_int	*first;

	first = (t_int *)malloc(sizeof(t_int));
	if (!first)
		return (NULL);
	first->digit = ft_atol(content);
	first->next = NULL;
	first->bnext = NULL;
	return (first);
}
