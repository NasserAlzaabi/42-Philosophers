/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 19:09:11 by naalzaab          #+#    #+#             */
/*   Updated: 2024/01/31 18:03:46 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_philo(t_able *table)
{
	if (table->philosophers)
		free(table->philosophers);
	return (1);
}

int	free_mutex(t_able *table, int n)
{
	t_fork	*tmp;
	int		i;

	i = 0;
	while (++i < n)
	{
		if (i + 1 < n)
			tmp = table->forks->next;
		pthread_mutex_destroy(&table->forks->fork_lock);
		free(table->forks);
		if (i + 1 < n)
			break ;
		table->forks = tmp;
	}
	return (1);
}

int free_all(t_able *table, int n)
{
	free_philo(table);
	free_mutex(table, n);
	return (1);
}

int	free_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->cur_fork->fork_lock);
	pthread_mutex_unlock(&philo->next_fork->fork_lock);
	return (1);
}