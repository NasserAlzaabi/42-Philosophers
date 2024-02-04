/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:23:14 by naalzaab          #+#    #+#             */
/*   Updated: 2024/02/04 14:39:42 by naalzaab         ###   ########.fr       */
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

int	assign_return(t_able *table, t_fork *forks, int i)
{
	table->forks = forks;
	free_all(table, i);
	return (1);
}

int	assign_ret(t_able *table, t_fork *forks)
{
	table->forks = forks;
	return (0);
}
