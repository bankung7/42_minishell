/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:09:12 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/02 20:23:43 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*ptr1;
	char	*ptr2;

	i = 0;
	ptr1 = (char *)s1;
	ptr2 = (char *)s2;
	while (i < n)
	{
		if ((unsigned char)ptr1[i] - (unsigned char)ptr2[i] != 0)
			return ((unsigned char)ptr1[i] - (unsigned char)ptr2[i]);
		i++;
	}
	return (0);
}
