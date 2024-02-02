/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:35:15 by naalzaab          #+#    #+#             */
/*   Updated: 2024/02/02 19:39:11 by naalzaab         ###   ########.fr       */
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
	table->t_start = (table->start_time.tv_sec * 1000) + (table->start_time.tv_usec / 1000); //convert to long milisecs
	while (i < table->num_of_philos)
	{
		table->philosophers[i].table = table;
		table->philosophers[i].id = i + 1;
		table->philosophers[i].cur_fork = tmp;
		table->philosophers[i].next_fork = tmp->next;
		tmp = tmp->next;
		pthread_create(&table->philosophers[i].thread, NULL, (void *)philos, &table->philosophers[i]);
		i++;
	}
	i = 0;
	while(i < table->num_of_philos)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
}
