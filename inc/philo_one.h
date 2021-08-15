#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

# define ERROR 0
# define SUCCESS 1
# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIED 5

struct s_board;

typedef struct s_philo
{
	int		order;
	int		tt_die;
	int		last_eat;
	int		lfork;
	int		rfork;
	int		nb_eat;
	int		is_finish;
	struct s_board	*global;
}				t_philo;

typedef struct s_board
{
	int				nb_eat;
	int				nbr_finish;
	struct timeval	timeval;
	int				dead_test;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				tt_think;
	long			t_begon;
	int				amount;
	t_philo 		*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	writting;
}				t_board;

int		ft_atoi_positive(const char *str);
void	*routine(void	*void_philo);
int		init_philo(t_board *board);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		get_time(t_board *board);
