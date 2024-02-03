/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:34:40 by naalzaab          #+#    #+#             */
/*   Updated: 2024/02/03 18:55:56 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_able	table;

	if (argc == 5 || argc == 6)
	{
		if (!check_args(argv))
		{
			write(2, "Error: invalid input", 20);
			return (1);
		}
		else if (argc == 6 && ft_atoi(argv[5]) < 1)
		{
			write(2, "Error: Number of times philo must eat must be at least 1",
				56);
			return (1);
		}
		init_args(argc, argv, &table);
		table.philosophers = ft_calloc(table.num_of_philos, sizeof(t_philo));
		if (!table.philosophers)
			return (free_philo(&table));
		if (assign_forks(&table) == 1)
			return (1); // create function to free evrything then return 1
		threads_init(&table);
		pthread_mutex_destroy(&table.writing);
		free_all(&table, table.num_of_philos);
	}
	else
		write(2, "Error: wrong number of inputs", 29);
	return (0);
}
