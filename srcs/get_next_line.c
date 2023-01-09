/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:19:00 by pjerddee          #+#    #+#             */
/*   Updated: 2023/01/10 00:56:49 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	int			nl_id;

	if (str == NULL)
	{
		str = ft_calloc(1, sizeof(char));
		if (!str)
			return (NULL);
	}
	str = ft_read(str, fd);
	if (str == NULL)
		return (str);
	nl_id = ft_strlen_nl(str, 1);
	if (nl_id < 0)
	{
		line = ft_lastline(str);
		str = NULL;
	}
	else
	{
		line = get_line(str, nl_id);
		str = get_remain(str, nl_id);
	}
	return (line);
}

//return the remaining of str after the first '\n'
char	*get_remain(char *s, int nl_id)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	tmp = ft_calloc(ft_strlen_nl(s, 0) - nl_id, sizeof(char));
	if (!tmp)
	{
		if (s != NULL)
			free(s);
		return (NULL);
	}
	while (s[nl_id + i + 1])
	{
		tmp[i] = s[nl_id + i + 1];
		i++;
	}
	if (s != NULL)
		free(s);
	return (tmp);
}

//return line before '\n'
char	*get_line(char *s, int nl_id)
{
	int		i;
	char	*line;

	i = 0;
	line = ft_calloc(nl_id + 2, sizeof(char));
	if (!line)
		return (NULL);
	while (i <= nl_id)
	{
		line[i] = s[i];
		i++;
	}
	return (line);
}

// return last line and free the static variable
char	*ft_lastline(char *str)
{
	char	*l_line;
	int		i;

	i = 0;
	l_line = ft_calloc(ft_strlen_nl(str, 0) + 1, sizeof(char));
	if (!l_line || !str)
	{
		if (str != NULL)
			free(str);
		return (NULL);
	}
	while (str[i])
	{
		l_line[i] = str[i];
		i++;
	}
	if (str != NULL)
		free(str);
	return (l_line);
}

char	*ft_read(char *str, int fd)
{
	char	*buf;
	ssize_t	ret;
	int		cur;

	cur = 0;
	while (1)
	{
		buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buf)
			return (NULL);
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret <= 0 && str[0] == '\0')
		{
			free(str);
			free(buf);
			return (NULL);
		}
		str = ft_strjoin(str, buf);
		if (!str)
			return (NULL);
		if (ft_strlen_nl(str + cur, 1) >= 0 || ret < BUFFER_SIZE)
			break ;
		cur += ft_strlen_nl(str + cur, 0);
	}
	return (str);
}
