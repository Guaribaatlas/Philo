#include "philo_one.h"


void	write_it(t_philo *philo, int wich)
{
	t_timeval tmp;
	int tmp_time;

	gettimeofday(&tmp, NULL);
	time_tmp = tmp.tv_usec - philo->global->timeval.tv_usec;
	if (wich == 1)
		printf("[%i] %i has taken a fork\n", time_tmp, philo->order);
	if (wich == 2)
		printf("[%i] %i is eating\n", philo->last_eat, philo->order);
	if (wich == 3)
		printf("[%i] %i is sleeping", time_tmp, philo->order);
	if (wich == 4)
		printf("[%i] %i is thinking", time_tmp, philo->order);
	if (wich == 5)
		printf("[%i] %i died", time_tmp, philo->order);

}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->global->fork[philo->lfork]);
	write_it(philo, 1);
	pthread_mutex_lock(philo->global->fork[philo->rfork];
	write_it(philo, 1);
	write_it(philo, 2);
	usleep(philo->global->tt_eat);
	pthread_mutex_unlock(philo->global->fork[philo->lfork]);
	pthread_mutex_unlock(philo->global->fork[philo->rfork];
}

void	philo_else(t_philo *philo)
{

	write_it(philo, 3);
	usleep(philo->global->tt_sleep);
	write_it(philo, 4);
	usleep(philo->global->tt_think);
}

void	routine(t_philo *philo)
{
	if (philo->nb_eat != 0)
	{
		while (philo->nb_eat < philo->global->nb_eat)
		{
			philo_eat(philo);
			philo_else(philo);
		}
	}
	else
	{
		while (1)
		{
			philo_eat(philo);
			philo_else(philo);
			if (philo->global->dead_test)
				break ;
		}
	}

}