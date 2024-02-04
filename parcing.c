/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:34:47 by naalzaab          #+#    #+#             */
/*   Updated: 2024/02/04 18:49:10 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(char **str)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (0);
			if (str[i][j] == '-')
				return (0);
			j++;
		}
		if (ft_atoi(str[i]) > INT_MAX || ft_atoi(str[i]) < INT_MIN)
			return (0);
		if (ft_atoi(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	init_args(int argc, char **av, t_able *table)
{
	table->num_of_philos = ft_atoi(av[1]);
	table->t_die = ft_atoi(av[2]);
	table->t_eat = ft_atoi(av[3]);
	table->t_sleep = ft_atoi(av[4]);
	table->any_dead = 0;
	if (pthread_mutex_init(&table->writing, NULL) != 0)
		return ;
	if (argc == 6)
		table->meals = ft_atoi(av[5]);
	else
		table->meals = -1;
}

t_fork	*create_fork(void)
{
	t_fork	*fork;

	fork = ft_calloc(1, sizeof(t_fork));
	if (!fork)
		return (NULL);
	fork->next = NULL;
	return (fork);
}

int	assign_forks(t_able *table)
{
	t_fork	*forks;
	t_fork	*tmp;
	int		i;

	i = 0;
	forks = NULL;
	while (++i <= table->num_of_philos)
	{
		tmp = create_fork();
		if (!tmp)
			return (1);
		tmp->fork_id = i;
		tmp->last_used = i;
		if (i % 2)
			tmp->last_used -= 1;
		if (i == 1)
			tmp->last_used = table->num_of_philos;
		if ((table->num_of_philos % 2) && (table->num_of_philos == i))
			tmp->last_used = i;
		ft_lstadd_back(&forks, tmp);
		if (pthread_mutex_init(&tmp->fork_lock, NULL) != 0)
			return (assign_return(table, forks, i));
	}
	tmp->next = forks;
	return (assign_ret(table, forks));
}
