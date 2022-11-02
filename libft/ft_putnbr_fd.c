/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 22:00:57 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/12 20:16:12 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	void	ft_printnbr(int n, int fd)
{
	char	m;

	if (n > 0)
	{
		m = (n % 10) + '0';
		ft_printnbr(n / 10, fd);
		write(fd, &m, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int	isneg;

	isneg = 0;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ((void)0);
	}
	if (n == -2147483648)
	{
		n /= -10;
		isneg = 2;
	}
	if (n < 0)
	{
		n *= -1;
		isneg = 1;
	}
	if (isneg > 0)
		write(fd, "-", 1);
	ft_printnbr(n, fd);
	if (isneg == 2)
		write(fd, "8", 1);
}
