#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>//idk
# include <stdio.h>//printf
# include <string.h>// idk
# include <stdlib.h>// malloc free exit success and failiure
# include <pthread.h>// anything related to threads
# include <stdbool.h>// bool
# include <limits.h>// intmax
# include <sys/time.h>

#define FORK "\e[1;97mtime:%d || Philo \e[1;95mid:%d \e[0m\e[1;97mis \e[1;95m[Has Taken A Fork]\n\e[0m"
#define EAT "\e[1;97mtime:%d || Philo \e[1;92mid:%d \e[0m\e[1;97mis \e[1;92m[eating]\n\e[0m"
#define SLEEP "\e[1;97mtime:%d || Philo \e[1;93mid:%d \e[0m\e[1;97mis \e[1;93m[sleeping]\n\e[0m"
#define THINK "\e[1;97mtime:%d || Philo \e[1;94mid:%d \e[0m\e[1;97mis \e[1;94m[thinking]\n\e[0m"
#define DEAD "\e[1;97mtime:%d || Philo \e[1;91mid:%d \e[0m\e[1;97mis \e[1;91m[dead]\n\e[0m"

typedef struct timeval t_ime;

typedef struct s_philo {
	int				id;
	long			is_dead;
	pthread_t		thread; //thread created for philo
	struct s_fork	*cur_fork;
	struct s_fork	*next_fork;
	struct timeval	last_eat;
	struct timeval	current_time;
	struct s_able *table;
} t_philo;

typedef struct s_fork {
	int 			fork_id;
	int				last_used;
	pthread_mutex_t fork_lock;
	struct s_fork	*next;
}	t_fork;

typedef struct s_able {
	long			t_die;
	long			t_sleep;
	long			t_eat;
	int 			num_of_philos;
	int				any_dead;
	int				meals;
	struct timeval	start_time;
	long			t_start;
	pthread_mutex_t	writing;
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
void	philos(void *arg);
int		wait_turn(t_philo *philo);
int		free_forks(t_philo *philo);
int		printl(t_philo *philo, char	*state);
int		eat(t_philo *philo);
int		eat_time(t_ime start, int	et);
int		reverse_run(t_philo *philo);
int		run(t_philo *philo);
void	threads_init(t_able *table);


#endif