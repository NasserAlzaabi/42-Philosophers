/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:21:12 by naalzaab          #+#    #+#             */
/*   Updated: 2024/02/04 18:26:40 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_dead(t_philo *philo)
{
	long	curtime;
	int		ret;

	ret = 0;
	gettimeofday(&philo->current_time, NULL);
	philo->is_dead = (philo->current_time.tv_sec * 1000
			+ philo->current_time.tv_usec / 1000) - (philo->last_eat.tv_sec
			* 1000 + philo->last_eat.tv_usec / 1000);
	curtime = (philo->current_time.tv_sec * 1000 + \
		philo->current_time.tv_usec / 1000) - philo->table->t_start;
	pthread_mutex_lock(&philo->table->writing);
	if (philo->table->any_dead)
		ret = 1;
	else if (philo->is_dead >= philo->table->t_die)
	{
		printf(DEAD, (int)(curtime), philo->id);
		philo->table->any_dead = 1;
		ret = 1;
	}
	pthread_mutex_unlock(&philo->table->writing);
	return (ret);
}

void	philos(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->num_of_philos == 1)
	{
		single_philo(philo);
		return ;
	}
	gettimeofday(&philo->last_eat, NULL);
	while (1)
	{
		if (philo->table->meals == 0)
			break ;
		if (printl(philo, THINK))
			break ;
		if (philo->id % 2)
		{
			if (run(philo))
				break ;
		}
		else if (reverse_run(philo))
			break ;
		if (sleepin(philo))
			break ;
	}
}

int	run(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->cur_fork->fork_lock);
		if (check_dead(philo))
			return (free_fork(philo, 1));
		pthread_mutex_lock(&philo->next_fork->fork_lock);
		if (philo->id != philo->next_fork->last_used
			&& philo->id != philo->cur_fork->last_used)
			break ;
		free_forks(philo);
		usleep(200);
	}
	free_forks(philo);
	if (printl(philo, FORK) || printl(philo, FORK))
		return (1);
	if (eat(philo) && philo->n_eats != philo->table->meals)
		return (1);
	pthread_mutex_lock(&philo->cur_fork->fork_lock);
	philo->cur_fork->last_used = philo->id;
	pthread_mutex_lock(&philo->next_fork->fork_lock);
	philo->next_fork->last_used = philo->id;
	free_forks(philo);
	if (philo->n_eats == philo->table->meals)
		return (1);
	return (0);
}

int	reverse_run(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->next_fork->fork_lock);
		if (check_dead(philo))
			return (free_fork(philo, 0));
		pthread_mutex_lock(&philo->cur_fork->fork_lock);
		if (philo->id != philo->next_fork->last_used
			&& philo->id != philo->cur_fork->last_used)
			break ;
		free_forks(philo);
		usleep(200);
	}
	free_forks(philo);
	if (printl(philo, FORK) || printl(philo, FORK))
		return (1);
	if (eat(philo) && philo->n_eats != philo->table->meals)
		return (1);
	pthread_mutex_lock(&philo->next_fork->fork_lock);
	philo->next_fork->last_used = philo->id;
	pthread_mutex_lock(&philo->cur_fork->fork_lock);
	philo->cur_fork->last_used = philo->id;
	free_forks(philo);
	if (philo->n_eats == philo->table->meals)
		return (1);
	return (0);
}
