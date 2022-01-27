/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 16:04:04 by jehaenec          #+#    #+#             */
/*   Updated: 2021/08/15 16:04:06 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>

# define ERROR 0
# define SUCCESS 1
# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIED 5
# define BUFF_SIZE 600

struct	s_board;

typedef struct s_philo
{
	int				order;
	int				tt_die;
	int				last_eat;
	int				lfork;
	int				rfork;
	int				nb_eat;
	int				is_finish;
	pthread_t		tid;
	struct s_board	*global;
}				t_philo;

typedef struct s_board
{
	int				nb_eat;
	int				nbr_finish;
	struct timeval	timeval;
	int				tt_die;
	int				is_finished;
	int				tt_eat;
	int				tt_sleep;
	long			t_begon;
	int				amount;
	char			buff[BUFF_SIZE];
	int				pos;
	int				start;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	add_finish;
	pthread_mutex_t	writting;
}				t_board;

int		ft_atoi_positive(const char *str);
void	*routine(void	*void_philo);
int		init_philo(t_board *board);
int		get_time(t_board *board);
int		ft_strlen(char *str);
void	transform(int time, t_philo *philo, char *str);
void	write_it(t_philo *philo, int wich);
void	flushbuff(t_philo *philo);

#endif
