/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:04:38 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/12 20:17:36 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	ft_count(unsigned int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static	int	ft_isneg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	int				neg;
	int				len;
	char			*ptr;
	unsigned int	nn;

	neg = ft_isneg(n);
	if (n < 0)
		nn = n * -1;
	else
		nn = n;
	len = ft_count(nn);
	ptr = ft_calloc(sizeof(char), (len + neg + 1));
	if (!ptr)
		return (0);
	ptr[0] = '-';
	if (nn == 0)
		ptr[0] = '0';
	while (nn > 0)
	{
		ptr[len + neg - 1] = (nn % 10) + '0';
		len--;
		nn /= 10;
	}
	return (ptr);
}
