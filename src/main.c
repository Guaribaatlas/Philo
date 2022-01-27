/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 16:05:05 by jehaenec          #+#    #+#             */
/*   Updated: 2021/08/24 16:12:39 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

int	ft_exit(t_board *board)
{
	int	i;

	i = 0;
	flushbuff(&board->philo[0]);
	board->is_finished = 1;
	while (i < board->amount)
	{
		pthread_join(board->philo[i].tid, NULL);
		i++;
	}
	free((void *)board->philo);
	i = 0;
	while (i < board->amount)
		pthread_mutex_destroy(&board->fork[i++]);
	free((void *)board->fork);
	pthread_mutex_destroy(&board->writting);
	pthread_mutex_destroy(&board->add_finish);
	return (SUCCESS);
}

int	verif_end(t_board *board)
{
	int	time_tmp;
	int	i;

	i = 0;
	while (1)
	{
		usleep(500);
		time_tmp = get_time(board);
		if (time_tmp - board->philo[i].last_eat > board->tt_die)
		{
			if (!board->philo[i].is_finish)
			{
				write_it(&board->philo[i], DIED);
				break ;
			}
		}
		if (board->nbr_finish == board->amount)
			break ;
		if (i == board->amount - 1)
			i = 0;
		else
			i++;
	}
	return (ft_exit(board));
}

int	parse_arg(t_board *board, char **arv, int arc)
{
	if (arc < 5 || arc > 6)
	{
		printf("to run : ./philosopher nbr, tt_die, tt_eat, tt_sleep.\n");
		return (ERROR);
	}
	board->amount = ft_atoi_positive(arv[1]);
	board->tt_die = ft_atoi_positive(arv[2]);
	board->tt_eat = ft_atoi_positive(arv[3]);
	board->tt_sleep = ft_atoi_positive(arv[4]);
	if (arc == 6)
		board->nb_eat = ft_atoi_positive(arv[5]);
	if (board->amount <= 0 || board->tt_die < 0 || board->tt_sleep < 0
		|| board->nb_eat < 0 || board->tt_eat < 0)
	{
		printf("nb_philo > 0 || only positive int for other args\n");
		return (ERROR);
	}
	if (arc != 6)
		board->nb_eat = -1;
	return (SUCCESS);
}

int	start_thread(t_board *board)
{
	int	i;

	i = 0;
	board->start = 0;
	while (i < board->amount)
	{
		if (pthread_create(&board->philo[i].tid, NULL, routine, (void *)
				&board->philo[i]) != 0)
			return (ERROR);
		i++;
	}
	board->start = 1;
	return (verif_end(board));
}

int	main(int arc, char **arv)
{
	t_board	board;

	board.nb_eat = 0;
	if (parse_arg(&board, arv, arc) == ERROR)
		return (ERROR);
	if (init_philo(&board) == ERROR)
		return (ERROR);
	if (start_thread(&board) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
