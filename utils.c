/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:35:20 by naalzaab          #+#    #+#             */
/*   Updated: 2024/01/22 19:25:29 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
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