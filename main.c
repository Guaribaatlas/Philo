#include "philo_one.h"

int		parse_arg(t_board *board, char **arv, int arc)
{
	if (arc < 5 || arc > 6)
		return (ERROR);
	board->amount = ft_atoi(arv[1]);
	board->fork = amount;
	board->tt_die = ft_atoi(arv[2]);
	board->tt_eat = ft_atoi(arv[3]);
	board->tt_slp = ft_atoi(arv[4]);
	return(SUCCESS);
}

int		start_thread(t_board *board)
{
	void	*tmp;
	int		i;

	i = 0;
	while (i < board->amount)
	{
		tmp = (void*)board->phil[i];
		if (pthread_create(&board->tab_th[i], &routine, tmp) == ERROR)
			return(ERROR);
		pthread_detach(&board->tab_th[i]);
		usleep(100);
		i++;
	}

}

int		main(int arc, char **arv)
{
	t_board  board;

	if (parse_arg(&board, arv, arc) == ERROR)
		return (ERROR);
	if (init_philo(&board) == ERROR)
		return (ERROR);
	if (start_thread(&board) == ERROR)
		return (ERROR);
	return(SUCCESS);
}