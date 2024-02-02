/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:44:43 by naalzaab          #+#    #+#             */
/*   Updated: 2024/02/02 21:26:19 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	printl(t_philo *philo, char	*state)
{
	long	time;
	long	s_time;
	
	gettimeofday(&philo->current_time, NULL);
	time = philo->current_time.tv_sec * 1000 + philo->current_time.tv_usec / 1000;
	s_time = philo->table->start_time.tv_sec * 1000 + philo->table->start_time.tv_usec / 1000;
	pthread_mutex_lock(&philo->table->writing);
	if (!philo->table->any_dead)
	{
		printf(state, time - s_time, philo->id);
		pthread_mutex_unlock(&philo->table->writing);
		return (0);
	}
	// printf(state, 100, philo->id);
	pthread_mutex_unlock(&philo->table->writing);
	return (1);
}
