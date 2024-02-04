/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:35:15 by naalzaab          #+#    #+#             */
/*   Updated: 2024/02/04 19:32:19 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	threads_init(t_able *table)
{
	int		i;
	t_fork	*tmp;

	i = 0;
	tmp = table->forks;
	gettimeofday(&table->start_time, NULL);
	table->t_start = (table->start_time.tv_sec * 1000)
		+ (table->start_time.tv_usec / 1000);
	while (i < table->num_of_philos)
	{
		table->philosophers[i].table = table;
		table->philosophers[i].id = i + 1;
		table->philosophers[i].n_eats = 0;
		table->philosophers[i].cur_fork = tmp;
		table->philosophers[i].next_fork = tmp->next;
		tmp = tmp->next;
		pthread_create(&table->philosophers[i].thread, NULL, (void *)philos,
			&table->philosophers[i]);
		i++;
	}
	i = -1;
	while (++i < table->num_of_philos)
		pthread_join(table->philosophers[i].thread, NULL);
}

void	single_philo(t_philo *philo)
{
	gettimeofday(&philo->last_eat, NULL);
	if (check_dead(philo))
		return ;
	if (printl(philo, THINK))
		return ;
	pthread_mutex_lock(&philo->cur_fork->fork_lock);
	if (printl(philo, FORK))
	{
		pthread_mutex_unlock(&philo->cur_fork->fork_lock);
		return ;
	}
	while (1)
	{
		if (check_dead(philo))
		{
			pthread_mutex_unlock(&philo->cur_fork->fork_lock);
			return ;
		}
	}
}

int	sleepin(t_philo *philo)
{
	t_ime	start_time;

	if (printl(philo, SLEEP))
		return (1);
	gettimeofday(&start_time, NULL);
	while (1)
	{
		if (check_dead(philo))
			return (1);
		usleep(200);
		if (wait_time(start_time, philo->table->t_sleep))
			break ;
	}
	return (0);
}

int	eat(t_philo *philo)
{
	if (printl(philo, EAT))
		return (1);
	gettimeofday(&philo->last_eat, NULL);
	while (1)
	{
		if (check_dead(philo))
			return (1);
		usleep(200);
		if (wait_time(philo->last_eat, philo->table->t_eat))
			break ;
	}
	if (philo->table->meals != -1)
	{
		philo->n_eats++;
		if (philo->n_eats == philo->table->meals)
			return (1);
	}
	return (0);
}

int	wait_time(t_ime start, int et)
{
	t_ime	cur_time;
	long	res;

	res = 0;
	gettimeofday(&cur_time, NULL);
	if (!et)
		et = 50;
	res = (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000) - (start.tv_sec
			* 1000 + start.tv_usec / 1000);
	if (res < 0)
		res += 1000;
	if (res >= et)
		return (1);
	return (0);
}
