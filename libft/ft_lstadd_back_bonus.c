/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waxxy <waxxy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:13:49 by tnoulens          #+#    #+#             */
/*   Updated: 2022/06/26 10:03:46 by waxxy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_int *lst, t_int *new)
{
	t_int	*pl;

	if (lst)
	{
		pl = ft_lstlast(lst);
		pl->next = new;
		new->bnext = pl;
	}
	else
		lst = new;
}
