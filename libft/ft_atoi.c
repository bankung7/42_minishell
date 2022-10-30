/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:14:54 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/12 19:18:38 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	val;

	i = 0;
	sign = 1;
	val = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]) != 0)
	{
		if (val * 10 + (str[i] - '0') > 2147483647 && sign > 0)
			return ((int)-1);
		if (val * 10 + (str[i] - '0') > 2147483648 && sign < 0)
			return ((int)0);
		val = val * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(val * sign));
}
