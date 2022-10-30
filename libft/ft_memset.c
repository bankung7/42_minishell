/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 23:28:04 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/11 13:54:31 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char		*cb;
	size_t		i;

	cb = (char *)b;
	i = 0;
	while (i < len)
		cb[i++] = (unsigned char)c;
	return (cb);
}
