/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:23:14 by naalzaab          #+#    #+#             */
/*   Updated: 2024/02/03 18:23:32 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_fork	*ft_lstlast(t_fork *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (!(lst->next))
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_fork **lst, t_fork *new)
{
	t_fork	*n;

	if (*lst)
	{
		n = ft_lstlast(*lst);
		n->next = &*new;
	}
	else
		*lst = new;
}
