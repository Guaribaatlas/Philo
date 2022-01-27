/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 16:04:56 by jehaenec          #+#    #+#             */
/*   Updated: 2021/08/15 16:04:58 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

int	get_time(t_board *board)
{
	struct timeval	tmp;
	long			calc;

	gettimeofday(&tmp, NULL);
	calc = (tmp.tv_sec * 1000) + (tmp.tv_usec / 1000);
	return ((int)(calc - board->t_begon));
}

int	mutex_init(t_board *board)
{
	int	i;

	board->pos = 0;
	pthread_mutex_init(&board->add_finish, NULL);
	pthread_mutex_init(&board->writting, NULL);
	board->fork = malloc(sizeof(pthread_mutex_t) * board->amount);
	if (board->fork == NULL)
	{
		free(board->philo);
		return (ERROR);
	}
	i = -1;
	while (++i < board->amount)
		pthread_mutex_init(&board->fork[i], NULL);
	return (SUCCESS);
}

int	init_philo(t_board *board)
{
	int	i;

	i = -1;
	board->nbr_finish = 0;
	board->is_finished = 0;
	board->philo = malloc(sizeof(t_philo) * board->amount);
	if (board->philo == NULL)
		return (ERROR);
	while (++i < board->amount)
	{
		board->philo[i].order = i;
		board->philo[i].last_eat = 0;
		board->philo[i].is_finish = 0;
		board->philo[i].global = board;
		board->philo[i].nb_eat = 0;
		board->philo[i].rfork = i;
		if (i == 0)
			board->philo[i].lfork = board->amount - 1;
		else
			board->philo[i].lfork = i - 1;
	}
	return (mutex_init(board));
}
