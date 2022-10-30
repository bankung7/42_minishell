/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 07:56:59 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/12 17:43:03 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	j;

	len = ft_strlen(dst);
	j = 0;
	if (len < dstsize - 1 && dstsize > 0)
	{
		while (src[j] && len < dstsize - j - 1)
		{
			dst[j + len] = src[j];
			j++;
		}
		dst[j + len] = 0;
	}
	if (len >= dstsize)
		len = dstsize;
	return (len + ft_strlen((char *)src));
}
