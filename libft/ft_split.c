/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:44:54 by vnilprap          #+#    #+#             */
/*   Updated: 2022/03/12 20:17:48 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static	int	ft_cstsplit(char const *s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (i > 0)
			if (s[i] == c && s[i - 1] != c)
				len++;
		if (s[i] != c && s[i + 1] == 0)
			len++;
		i++;
	}
	len++;
	return (len);
}

static	char	**ft_free(char **str)
{
	int		i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (0);
}

static	char	**ft_spliter(char const *s, char c)
{
	int		i;
	int		len;
	int		index;
	char	**ptr;

	i = 0;
	len = 0;
	index = 0;
	ptr = malloc(sizeof(char *) * ft_cstsplit(s, c));
	if (!ptr)
		return (0);
	while (s[i])
	{
		if (s[i] != c && s[i + 1] == 0)
			ptr[index++] = ft_substr(s, len, i - len + 1);
		if (s[i] == c && i > 0 && s[i - 1] != c)
			ptr[index++] = ft_substr(s, len, i - len);
		if (index > 0 && ptr[index - 1] == 0)
			return (ft_free(ptr));
		if (s[i] == c)
			len = i + 1;
		i++;
	}
	ptr[index] = 0;
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;

	if (!s)
	{
		ptr = (char **)ft_calloc(sizeof(char *), 1);
		if (!ptr)
			return (0);
		return (ptr);
	}
	ptr = ft_spliter(s, c);
	return (ptr);
}
