/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:35:20 by naalzaab          #+#    #+#             */
/*   Updated: 2024/01/25 17:13:16 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v')
		return (1);
	if (c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	x;
	int					s;
	int					n;

	s = 1;
	i = 0;
	x = 0;
	while (space(str[i]))
		i++;
	while (str[i] == '-' && ++i)
		s *= -1;
	while (str[i] == '+')
		i++;
	n = i;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	while (str[n] >= '0' && str[n] <= '9')
		x = x * 10 + (str[n++] - 48);
	return (x * s);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*str;

	i = 0;
	str = malloc(count * size);
	if (!str)
		return (0);
	while (i < (count * size))
		((char *)str)[i++] = '\0';
	return (str);
}

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
