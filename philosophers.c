/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:34:53 by naalzaab          #+#    #+#             */
/*   Updated: 2024/02/02 20:57:08 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_dead(t_philo *philo)
{
	gettimeofday(&philo->current_time, NULL);
	philo->is_dead = (philo->current_time.tv_sec * 1000 + philo->current_time.tv_usec / 1000) -\
	(philo->last_eat.tv_sec * 1000 + philo->last_eat.tv_usec / 1000);
	// printf("%d ded %ld\n", philo->id, philo->is_dead);
	// printf("%d tded %ld\n", philo->id, philo->table->t_die);
	if (philo->is_dead >= philo->table->t_die)
	{
		pthread_mutex_lock(&philo->table->writing);
		//free
		printf(DEAD, 100, philo->id);
		philo->table->any_dead = 1;
		pthread_mutex_unlock(&philo->table->writing);
		return (1);
	}
	return (0);
}

int	sleepin(t_philo *philo)
{
	t_ime start_time;

	// printf("ut\n");
	if (printl(philo, SLEEP))
		return(1);
	gettimeofday(&start_time, NULL);
	while (1)
	{
		if (check_dead(philo))
			return (1);
		if (philo->table->any_dead)
			return (1);
		usleep(200);
		if (eat_time(start_time, philo->table->t_sleep))
			break ;
	}
	return (0);
}

void	philos(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->table->num_of_philos == 1)
		;// make function to handle 1 philo
	gettimeofday(&philo->last_eat, NULL);
	while (1)
	{
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

int	wait_turn(t_philo *philo)
{
	gettimeofday(&philo->last_eat, NULL);
	philo->is_dead = philo->last_eat.tv_sec * 1000 + philo->last_eat.tv_usec / 1000;
	if (philo->is_dead >= philo->table->t_start)
		return (0);
	return (1);
}

int	free_fork(t_philo *philo, int whos_fork)
{
	if (whos_fork)
		pthread_mutex_unlock(&philo->cur_fork->fork_lock);
	else
		pthread_mutex_unlock(&philo->next_fork->fork_lock);
	return (1);
}

int	run(t_philo *philo)
{
	while (1)
	{
		// printf("%d o\n", philo->id);
		pthread_mutex_lock(&philo->cur_fork->fork_lock);
		if (check_dead(philo))
			return (free_fork(philo, 1));
		// printf("%d oo\n", philo->id);
		pthread_mutex_lock(&philo->next_fork->fork_lock);
		// printf("%d ooo\n", philo->id);
		if (philo->id != philo->next_fork->last_used && philo->id != philo->cur_fork->last_used)
			break ;
		free_forks(philo);
		// printf("%d oooo\n", philo->id);
		usleep(250);
	}
	// printf("%d free\n", philo->id);
	free_forks(philo);
	if (printl(philo, FORK) || printl(philo, FORK))
		return (1);
	gettimeofday(&philo->last_eat, NULL);
	if (eat(philo))
		return (1);
	pthread_mutex_lock(&philo->cur_fork->fork_lock);
	philo->cur_fork->last_used = philo->id;
	pthread_mutex_lock(&philo->next_fork->fork_lock);
	philo->next_fork->last_used = philo->id;
	free_forks(philo);
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
		if (philo->id != philo->next_fork->last_used && philo->id != philo->cur_fork->last_used)
			break ;
		free_forks(philo);
		usleep(250);
	}
	// printf("%d free\n", philo->id);
	free_forks(philo);
	if (printl(philo, FORK) || printl(philo, FORK))
		return (1);
	gettimeofday(&philo->last_eat, NULL);
	if (eat(philo))
		return (1);
	pthread_mutex_lock(&philo->cur_fork->fork_lock);
	philo->cur_fork->last_used = philo->id;
	pthread_mutex_lock(&philo->next_fork->fork_lock);
	philo->next_fork->last_used = philo->id;
	free_forks(philo);
	return (0);
}

int	eat(t_philo *philo)
{
	t_ime start_time;

	if (printl(philo, EAT))
		return(1);
	gettimeofday(&start_time, NULL);
	while (1)
	{
		if (check_dead(philo))
			return (1);
		if (philo->table->any_dead)
			return (1);
		usleep(200);
		if (eat_time(start_time, philo->table->t_eat))
			break ;
	}
	gettimeofday(&philo->last_eat, NULL);
	return (0);
}

int	eat_time(t_ime start, int et)
{
	t_ime	cur_time;
	long	res;

	res = 0;
	gettimeofday(&cur_time, NULL);
	if (!et)
		et = 50;
	res = (cur_time.tv_sec * 1000 + cur_time.tv_usec / 1000) - (start.tv_sec * 1000 + start.tv_usec / 1000);
	if (res < 0)
		res += 1000;
	if (res >= et)
		return (1);
	return (0);
}
