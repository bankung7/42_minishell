/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 23:28:20 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/03 07:48:14 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen((char *)s);
	if (*s == 0 && c != 0)
		return (0);
	while (s[i] != (char)c)
	{
		if (i == 0)
			return (0);
		i--;
	}
	return ((char *)(s + i));
}
