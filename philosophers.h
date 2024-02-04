/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:25:20 by naalzaab          #+#    #+#             */
/*   Updated: 2024/02/04 18:29:02 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define FORK "\e[1;97mTime: %d || Philosopher \e[1;95mID: %d\
\e[1;95m[Has Taken A Fork]\n\e[0m"
# define EAT "\e[1;97mTime: %d || Philosopher \e[1;92mID: %d\
 \e[1;92m[Is Eating]\n\e[0m"
# define SLEEP "\e[1;97mTime: %d || Philosopher \e[1;93mID: %d\
 \e[1;93m[Is Sleeping]\n\e[0m"
# define THINK "\e[1;97mTime: %d || Philosopher \e[1;94mID: %d\
 \e[1;94m[Is Thinking]\n\e[0m"
# define DEAD "\e[1;97mTime: %d || Philosopher \e[1;91mID: %d\
 \e[1;91m[Is Dead]\n\e[0m"

typedef struct timeval	t_ime;

typedef struct s_philo
{
	int					id;
	int					n_eats;
	long				is_dead;
	pthread_t			thread;
	struct s_fork		*cur_fork;
	struct s_fork		*next_fork;
	struct timeval		last_eat;
	struct timeval		current_time;
	struct s_able		*table;
}						t_philo;

typedef struct s_fork
{
	int					fork_id;
	int					last_used;
	pthread_mutex_t		fork_lock;
	struct s_fork		*next;
}						t_fork;

typedef struct s_able
{
	long				t_die;
	long				t_sleep;
	long				t_eat;
	int					num_of_philos;
	int					any_dead;
	int					meals;
	struct timeval		start_time;
	long				t_start;
	pthread_mutex_t		writing;
	t_philo				*philosophers;
	t_fork				*forks;
}						t_able;

int						ft_isdigit(int c);
int						check_args(char **str);
int						ft_atoi(const char *str);
void					init_args(int argc, char **av, t_able *table);
int						assign_forks(t_able *table);
void					*ft_calloc(size_t count, size_t size);
void					ft_lstadd_back(t_fork **lst, t_fork *new);
int						free_mutex(t_able *table, int n);
int						free_philo(t_able *table);
int						free_all(t_able *table, int n);
void					philos(void *arg);
int						wait_turn(t_philo *philo);
int						free_forks(t_philo *philo);
int						printl(t_philo *philo, char *state);
int						eat(t_philo *philo);
int						wait_time(t_ime start, int et);
int						reverse_run(t_philo *philo);
int						run(t_philo *philo);
void					threads_init(t_able *table);
int						check_dead(t_philo *philo);
void					single_philo(t_philo *philo);
int						wait_turn(t_philo *philo);
int						free_fork(t_philo *philo, int whos_fork);
int						sleepin(t_philo *philo);
int						wait_time(t_ime start, int et);
int						eat(t_philo *philo);
int						print_error(void);
int						assign_return(t_able *table, t_fork *forks, int i);
int						assign_ret(t_able *table, t_fork *forks);

#endif