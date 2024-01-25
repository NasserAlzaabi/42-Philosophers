#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>//idk
# include <stdio.h>//printf
# include <string.h>// idk
# include <stdlib.h>// malloc free exit success and failiure
# include <pthread.h>// anything related to threads
# include <stdbool.h>// bool
# include <limits.h>// intmax

typedef struct timeval t_val;

typedef struct s_philo {
	int				id;
	int				is_dead;
	pthread_t		p_thread; //thread created for philo
	struct s_fork	*cur_fork;
	struct s_fork	*next_fork;
	struct timeval	last_eat;
	struct timeval	current_time;
} t_philo;

typedef struct s_fork {
	int 			fork_id;
	int				last_used;
	pthread_mutex_t fork_lock;
	struct s_fork	*next;
}	t_fork;

typedef struct s_able {
	long	t_die;
	long	t_sleep;
	long	t_eat;
	int 	num_of_philos;
	int		any_dead;
	int		meals;
	t_philo	*philosophers;
	t_fork	*forks; //pointer to first (id = 1) fork in a circular linked list of forks
}	t_able;

int		ft_isdigit(int c);
int		check_args(char **str);
int		ft_atoi(const char *str);
void	init_args(int argc, char **av, t_able *table);
int		assign_forks(t_able *table);
void	*ft_calloc(size_t count, size_t size);
void	ft_lstadd_back(t_fork **lst, t_fork *new);
int		free_mutex(t_able *table, int n);
int		free_philo(t_able *table);
int		free_all(t_able *table, int n);



#endif