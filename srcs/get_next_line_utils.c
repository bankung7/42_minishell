/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:48:47 by pjerddee          #+#    #+#             */
/*   Updated: 2022/12/08 21:05:34 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strlen_nl(char *s, int sel);
char	*ft_strcpy(char *dst, char *src);
// char	*ft_strjoin(char *s1, char *s2);
// char	*ft_calloc(size_t n);

// 0 - return len of s without '\0'
// 1 - return '\n' id if exists, return -1 otherwise
int	ft_strlen_nl(char *s, int sel)
{
	int	i;

	i = 0;
	if (sel == 0)
	{
		i = 0;
		while (s[i] != '\0')
			i++;
		return (i);
	}
	else
	{
		while (s[i] != 0)
		{
			if (s[i] == '\n')
				return (i);
			i++;
		}
		return (-1);
	}
}

char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}