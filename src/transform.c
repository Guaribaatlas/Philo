#include "../inc/philo_one.h"

void	flushbuff(t_philo *philo)
{
	write(1, philo->global->buff, philo->global->pos);
	philo->global->pos = 0;
}

void	cinbuff(t_philo *philo, char c)
{
	if (philo->global->pos == BUFF_SIZE - 1)
		flushbuff(philo);
	philo->global->buff[philo->global->pos] = c;
	philo->global->pos++;
}

void	ft_putstr(char *str, t_philo *philo)
{
	int	i;

	i = 0;
	while (str[i])
	{
		cinbuff(philo, str[i]);
		i++;
	}
}

void	ft_putnbr(int nb, t_philo *philo)
{
	if (nb < 0)
	{
		cinbuff(philo, '-');
		nb++;
		nb = -nb;
		if (nb == 2147483647)
		{
			cinbuff(philo, 2);
			nb = 147483647;
		}
		nb++;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10, philo);
	}
	cinbuff(philo, nb % 10 + '0');
}

void	transform(int time, t_philo *philo, char *str)
{
	ft_putnbr(time, philo);
	cinbuff(philo, ' ');
	ft_putnbr(philo->order + 1, philo);
	cinbuff(philo, ' ');
	ft_putstr(str, philo);
	cinbuff(philo, '\n');
}
