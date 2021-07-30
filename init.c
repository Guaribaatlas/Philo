#include "philo_one.h"

int		mutex_init(t_board *board)
{
	int i;

	pthread_mutex_init(board->nb_finish, NULL);
	board->tab_th = malloc(sizeof(pthread_t) * board->amount);
	if (board->tab_th == NULL)
	{
		free(board->phil);
		return (ERROR);
	}
	board->fork = malloc(sizeof(pthread_mutex_t) * board->amount);
	if (board->fork == NULL)
	{
		free(board->phil);
		free(board->tab_th);
		return(ERROR);
	}
	i = -1;
	while (++i < board->amount)
		pthread_mutex_init(board->fork[i], NULL);
}

int		init_philo(t_board *board)
{
	int i;
	i = -1;
	gettimeofday(&board->timeval, NULL);
	board->dead_test = 0;
	board->philo = malloc(sizeof(t_philo) * amount);
	if (board-philo == NULL)
		return (ERROR);
	while (++i < board->amount)
	{
		board->philo[i].global = board;
		board->philo[i]
		board->philo[i].is_dead = 0;
		board->philo[i].rfork = i;
		if (i == 0)
			philo[i].lfork = board->amount - 1;
		else
			philo[i].lfork = i - 1;
	}
	return(mutex_init(board));
}