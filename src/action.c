#include "../inc/philo_one.h"

void	write_it(t_philo *philo, int wich)
{
	struct timeval tmp;
	int time_tmp;
	long	calc;


	pthread_mutex_lock(&philo->global->writting);
	gettimeofday(&tmp, NULL);
	calc = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
	time_tmp = (int)(calc - philo->global->t_begon);
	if (wich == 1)
		printf("[%i] %i has taken a fork\n", time_tmp, philo->order + 1);
	if (wich == 2)
	{
		philo->last_eat = time_tmp;
		printf("[%i] %i is eating\n", time_tmp, philo->order + 1);
	}
	if (wich == 3)
		printf("[%i] %i is sleeping\n", time_tmp, philo->order + 1);
	if (wich == 4)
		printf("[%i] %i is thinking\n", time_tmp, philo->order + 1);
	if (wich == 5)
		printf("[%i] %i died\n", time_tmp, philo->order + 1);
	pthread_mutex_unlock(&philo->global->writting);
}

void	philo_eat(t_philo *philo)
{
	struct timeval tmp;
	long time_tmp;
	long	calc;

	pthread_mutex_lock(&philo->global->fork[philo->lfork]);
	write_it(philo, FORK);
	if (philo->global->amount == 1)
		return;
	pthread_mutex_lock(&philo->global->fork[philo->rfork]);
	write_it(philo, FORK);
	write_it(philo, EAT);
	gettimeofday(&tmp, NULL);
	calc = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
	time_tmp = calc;
	while (time_tmp - calc < philo->global->tt_eat)
	{
		gettimeofday(&tmp, NULL);
		time_tmp = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
		usleep(1000);
	}
	if (++philo->nb_eat  == philo->global->nb_eat)
	{
		philo->is_finish = 1;
		philo->global->nbr_finish++;
	}
	pthread_mutex_unlock(&philo->global->fork[philo->lfork]);
	pthread_mutex_unlock(&philo->global->fork[philo->rfork]);
}

void	philo_else(t_philo *philo)
{
	struct timeval tmp;
	long time_tmp;
	long	calc;

	write_it(philo, SLEEP);
	gettimeofday(&tmp, NULL);
	calc = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
	time_tmp = calc;
	while (time_tmp - calc < philo->global->tt_sleep)
	{
		gettimeofday(&tmp, NULL);
		time_tmp = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
		usleep(1000);
	}
	write_it(philo, THINK);
}

void	*routine(void	*void_philo)
{
	t_philo *philo;

	philo = (t_philo *) void_philo;
	while (1)
	{
		philo_eat(philo);
		if (philo->is_finish || philo->global->amount == 1)
			break;
		philo_else(philo);
	}
	return (NULL);
}