#include "philo_one.h"

void	fct_write(t_philo *philo, int action)
{
	t_timeval tmp;

	gettimeofday(&tmp, NULL);
	printf("[%i] %i ", (tmp.tv_usec - philo->global->timeval.tv_usec),
		   philo->order);
	if (action == EAT)
	{

		printf("is eating\n");
	}
	if (action == THINK)
	{
		printf("is thinking\n");
	}
	if (action == SLEEP)
	{
		printf("is sleeping\n");
	}
	if (action == DIED)
	{
		printf("died\n");
	}

}

void	philo_eat(t_philo *philo)
{
	t_timeval tmp;
	int		time_tmp;

	pthread_mutex_lock(philo->global->fork[philo->lfork]);
	gettimeofday(&tmp, NULL);
	time_tmp = tmp.tv_usec - philo->global->timeval.tv_usec;
	printf("[%i] %i has taken a fork\n", time_tmp, philo->order);
	pthread_mutex_lock(philo->global->fork[philo->rfork];
	printf("[%i] %i has taken a fork\n", time_tmp, philo->order);
	gettimeofday(&tmp, NULL);
	philo->last_eat = tmp.tv_usec - philo->global->timeval.tv_usec;
	printf("[%i] %i is eating\n", philo->last_eat, philo->order);
	usleep(philo->global->tt_eat);
	pthread_mutex_unlock(philo->global->fork[philo->lfork]);
	pthread_mutex_unlock(philo->global->fork[philo->rfork];
	return (0);
}

void	philo_else(t_philo *philo)
{
	int		time_tmp;
	t_timeval tmp;

	gettimeofday(&tmp, NULL);
	time_tmp = tmp.tv_usec - philo->global->timeval.tv_usec;
	printf("[%i] %i is sleeping", time_tmp, philo->order);
	usleep(philo->global->tt_sleep);
	gettimeofday(&tmp, NULL);
	time_tmp = tmp.tv_usec - philo->global->timeval.tv_usec;
	printf("[%i] %i is thinking", time_tmp, philo->order);
	usleep(philo->global->tt_think);
}

void	routine(t_philo *philo)
{
	if (philo->global->nb_eat != 0)
	{
		while (philo->global->nb_finish != philo->global->amount)
		{
			philo_eat(philo);
			philo_else(philo);
		}
	}
	else
	{
		while (1)
		{
			if (philo->global->dead_test)
				break ;
		}
	}

}