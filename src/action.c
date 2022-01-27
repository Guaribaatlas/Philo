/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 16:04:31 by jehaenec          #+#    #+#             */
/*   Updated: 2021/08/24 16:12:41 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

void	do_sleep(t_philo *philo, int type)
{
	struct timeval	tmp;
	long			time_tmp;
	long			calc;

	gettimeofday(&tmp, NULL);
	calc = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
	time_tmp = calc;
	while (time_tmp - calc < type && !philo->global->is_finished)
	{
		gettimeofday(&tmp, NULL);
		time_tmp = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
		usleep(500);
	}
}

void	write_it(t_philo *philo, int wich)
{
	struct timeval	tmp;
	int				time_tmp;
	long			calc;

	pthread_mutex_lock(&philo->global->writting);
	gettimeofday(&tmp, NULL);
	calc = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
	time_tmp = (int)(calc - philo->global->t_begon);
	if (wich == 1 && !(philo->global->is_finished))
		transform(time_tmp, philo, "has taken a fork");
	if (wich == 2 && !(philo->global->is_finished))
	{
		philo->last_eat = time_tmp;
		transform(time_tmp, philo, "is eating");
	}
	if (wich == 3 && !(philo->global->is_finished))
		transform(time_tmp, philo, "is sleeping");
	if (wich == 4 && !(philo->global->is_finished))
		transform(time_tmp, philo, "is thinking");
	if (wich == 5 && !(philo->global->is_finished))
	{
		transform(time_tmp, philo, "died");
		philo->global->is_finished = 1;
	}
	pthread_mutex_unlock(&philo->global->writting);
}

void	philo_eat(t_philo *philo)
{
	if (philo->nb_eat == 0 && philo->order % 2 == 0)
		usleep(philo->global->tt_eat * 900 + 1000);
	pthread_mutex_lock(&philo->global->fork[philo->lfork]);
	write_it(philo, FORK);
	if (philo->global->amount == 1)
		return ;
	pthread_mutex_lock(&philo->global->fork[philo->rfork]);
	write_it(philo, FORK);
	write_it(philo, EAT);
	do_sleep(philo, philo->global->tt_eat);
	if (++philo->nb_eat == philo->global->nb_eat)
	{
		philo->is_finish = 1;
		pthread_mutex_lock(&philo->global->add_finish);
		philo->global->nbr_finish++;
		pthread_mutex_unlock(&philo->global->add_finish);
	}
	pthread_mutex_unlock(&philo->global->fork[philo->lfork]);
	pthread_mutex_unlock(&philo->global->fork[philo->rfork]);
}

void	philo_else(t_philo *philo)
{
	write_it(philo, SLEEP);
	do_sleep(philo, philo->global->tt_sleep);
	write_it(philo, THINK);
}

void	*routine(void	*void_philo)
{
	t_philo	*philo;

	philo = (t_philo *) void_philo;
	while (1)
	{
		if (philo->global->start == 1)
			break ;
	}
	gettimeofday(&philo->global->timeval, NULL);
	philo->global->t_begon = (philo->global->timeval.tv_sec * 1000)
		+ (philo->global->timeval.tv_usec / 1000);
	philo->last_eat = 0;
	while (1)
	{
		philo_eat(philo);
		if (philo->is_finish || philo->global->is_finished == 1
			|| philo->global->amount == 1)
			break ;
		philo_else(philo);
		usleep(500);
	}
	return (NULL);
}
