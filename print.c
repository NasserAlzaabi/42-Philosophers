/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:44:43 by naalzaab          #+#    #+#             */
/*   Updated: 2024/02/04 14:21:33 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	printl(t_philo *philo, char *state)
{
	long	time;

	gettimeofday(&philo->current_time, NULL);
	time = philo->current_time.tv_sec * 1000 + philo->current_time.tv_usec
		/ 1000;
	pthread_mutex_lock(&philo->table->writing);
	if (!philo->table->any_dead)
	{
		printf(state, time - philo->table->t_start, philo->id);
		pthread_mutex_unlock(&philo->table->writing);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->writing);
	return (1);
}

int	print_error(void)
{
	write(2, "Error: invalid input", 20);
	return (1);
}
