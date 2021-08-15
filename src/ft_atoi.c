/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 09:41:22 by jehaenec          #+#    #+#             */
/*   Updated: 2019/10/27 20:36:41 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

static int	ft_verif(long nb)
{
	if (nb > INT_MAX)
		return (-1);
	return (1);
}

int			ft_atoi_positive(const char *str)
{
	int			m;
	long long	nb;
	int			r;

	nb = 0;
	m = 1;
	while (*str == '\t' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = ((nb * 10) + *str) - 48;
		str++;
	}
	if (*str != '\0')
	{
		return (-1);
	}
	r = ft_verif(nb);
	if (r == -1)
		return (r);
	return (nb * m);
}
