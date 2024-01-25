/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 17:34:40 by naalzaab          #+#    #+#             */
/*   Updated: 2024/01/25 19:21:38 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//inputs: number of philosophers, time till death, time eating takes, time sleeping takes, optional (number of times each philo must eat)
int main(int argc, char **argv)
{
	t_able table;

	if (argc == 5 || argc == 6)
	{
		if (!check_args(argv)) //start here
		{
			write(2, "Error: invalid input", 20);
			return 1;
		}
		else if (argc == 6 && ft_atoi(argv[5]) < 1)
		{
			write(2, "Error: Number of times philo must eat must be at least 1", 56);
			return (1);
		} //create function for checking args and return 1 template(return check_all_args())end here
		init_args(argc, argv, &table);
		table.philosophers = ft_calloc(table.num_of_philos, sizeof(t_philo));
		if (!table.philosophers)
			return (free_philo(&table));
		if (assign_forks(&table) == 1)
			return (1); //create function to free evrything then return 1
		int i = 0;
		while (i < table.num_of_philos)
		{
			printf("Id: %d\n", table.forks->fork_id);
			table.forks = table.forks->next;
			i++;
		}
	}
	else
		write(2, "Error: wrong number of inputs", 29);
	return (0);
}