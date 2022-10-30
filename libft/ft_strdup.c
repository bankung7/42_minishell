/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 21:59:21 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/12 19:27:28 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	len;

	len = ft_strlen((char *)s1) + 1;
	ptr = malloc(sizeof(char) * len);
	if (!ptr)
		return (0);
	ft_memmove(ptr, s1, len);
	return (ptr);
}
