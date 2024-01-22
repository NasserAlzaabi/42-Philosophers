/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:34:40 by naalzaab          #+#    #+#             */
/*   Updated: 2024/01/22 19:27:55 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//inputs: number of philosophers, time till death, time eating takes, time sleeping takes, optional (number of times each philo must eat)
int main(int argc, char **argv)
{
	t_able table;

	if (argc == 5 || argc == 6)
	{
		if (!check_args(argv))
		{
			write(2, "Error: invalid input", 20);
			return 1;
		}
		else if (ft_atoi(argv[5]) < 1)
		{
			write(2, "Error: Number of times philo must eat must be at least 1", 56);
			return 1;
		}
		init_args(argc, argv, &table);
		table.philosophers = ft_calloc(table.num_of_philos, sizeof(t_philo));
		if (!table.philosophers)
			return 1;
		assign_forks(&table);
	}
	else
		write(2, "Error: wrong number of inputs", 29);
}