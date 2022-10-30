/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 21:33:48 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/12 20:18:10 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*ptr;

	if (!s2)
		return (ft_strdup(s1));
	if (!s1)
		return (ft_strdup(s2));
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	ptr = ft_calloc(sizeof(char), (len1 + len2 + 1));
	if (!ptr)
		return (0);
	ft_memmove(ptr, s1, len1);
	ft_memmove(ptr + len1, s2, len2);
	return (ptr);
}
