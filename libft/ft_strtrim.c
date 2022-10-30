/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 08:07:25 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/12 20:17:56 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	ft_cchar(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (0);
		else
			i++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		i;
	int		end;
	char	*p;

	start = 0;
	if (!s1 || !set)
		return (0);
	end = ft_strlen((char *)s1) - 1;
	if (ft_strlen((char *)set) == 0)
		return (ft_strdup(s1));
	while (s1[start] && ft_cchar(s1[start], set) == 0)
		start++;
	while (end >= 0 && ft_cchar(s1[end], set) == 0)
		end--;
	if (start > (int)end)
		return (ft_calloc(sizeof(char), 1));
	i = (int)end - start + 1;
	p = ft_substr(s1, start, i);
	return (p);
}
