/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 09:41:22 by jehaenec          #+#    #+#             */
/*   Updated: 2021/08/15 16:04:46 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_one.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static int	ft_verif(long nb)
{
	if (nb > INT_MAX)
		return (-1);
	return (1);
}

int	ft_atoi_positive(const char *str)
{
	int			m;
	long long	nb;
	int			r;

	nb = 0;
	m = 1;
	if (ft_strlen((char *)str) > 11)
		return (-1);
	while (*str == '\t' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = ((nb * 10) + *str) - 48;
		str++;
	}
	r = ft_verif(nb);
	if (r == -1 || *str != '\0')
		return (-1);
	return (nb * m);
}
