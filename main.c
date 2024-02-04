/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:34:40 by naalzaab          #+#    #+#             */
/*   Updated: 2024/02/04 18:49:41 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_able	table;

	if (argc == 5 || argc == 6)
	{
		if (!check_args(argv))
			return (print_error());
		else if (argc == 6 && ft_atoi(argv[5]) < 0)
		{
			write(2, "Error: # of meals has to be positive", 36);
			return (1);
		}
		init_args(argc, argv, &table);
		table.philosophers = ft_calloc(table.num_of_philos, sizeof(t_philo));
		if (!table.philosophers)
			return (free_philo(&table));
		if (assign_forks(&table) == 1)
			return (1);
		threads_init(&table);
		pthread_mutex_destroy(&table.writing);
		free_all(&table, table.num_of_philos);
	}
	else
		write(2, "Error: wrong number of inputs", 29);
	return (0);
}
