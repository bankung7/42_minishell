/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <vnilprap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:04:19 by vnilprap          #+#    #+#             */
/*   Updated: 2023/01/22 21:04:21 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_addtoken(t_data *data, char *str, int type)
{
	t_token	*node;
	t_token	*head;

	node = malloc(sizeof(t_token));
	if (!node)
		return (-1);
	node->str = str;
	node->type = type;
	node->len = 0;
	node->next = 0;
	if (data->token == 0)
		data->token = node;
	else
	{
		head = data->token;
		while (head->next)
			head = head->next;
		head->next = node;
	}
	return (0);
}

int	ft_reargv(t_data *data, char *str)
{
	int		i;
	char	**tmp;
	t_cmd	*head;

	head = ft_lastcmd(data->cmdlist);
	tmp = malloc(sizeof(char *) * (ft_arrlen(head->argv) + 2));
	i = 0;
	while (head->argv && head->argv[i])
	{
		tmp[i] = head->argv[i];
		i++;
	}
	tmp[i++] = ft_strdup(str);
	tmp[i] = 0;
	free(head->argv);
	head->argv = tmp;
	return (0);
}
