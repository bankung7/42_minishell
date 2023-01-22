/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <vnilprap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:05:24 by vnilprap          #+#    #+#             */
/*   Updated: 2023/01/22 21:05:24 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Xpande which split is move to expander2.x
int	ft_setexpd(t_data *data, t_token *token, int i, t_expd *stc)
{
	int	j;

	j = 1;
	while (token->str[i + j] && (ft_isalnum(token->str[i + j]) == 1
			|| token->str[i + j] == '_'))
		j++;
	if (ft_strncmp("$?", &token->str[i], 2) == 0)
	{
		stc->tmp = ft_strdup("?");
		stc->env = ft_itoa(g_status);
		j++;
	}
	else
	{
		stc->tmp = ft_substr(token->str, i + 1, j - 1);
		stc->env = ft_getenv(data, stc->tmp);
	}
	return (j);
}

int	ft_getexpand(t_data *data, t_token *token, int i)
{
	int		j;
	int		len;
	t_expd	stc;

	j = ft_setexpd(data, token, i, &stc);
	stc.new = ft_calloc(sizeof(char), ft_strlen(token->str)
			+ (ft_strlen(stc.env) - ft_strlen(stc.tmp)) + 1);
	if (stc.tmp == 0 || stc.new == 0)
		return (ft_freetoken(data, -1));
	len = ft_strlen(stc.env);
	ft_memcpy(stc.new, token->str, i);
	ft_memcpy(&stc.new[ft_strlen(stc.new)], stc.env, ft_strlen(stc.env));
	ft_memcpy(&stc.new[ft_strlen(stc.new)], &token->str[i + j],
		ft_strlen(token->str) - (i + j));
	free(token->str);
	free(stc.tmp);
	free(stc.env);
	token->str = stc.new;
	return (len);
}

int	ft_expander(t_data *data, t_token *token, int x)
{
	int	i;

	i = 0;
	if (ft_strlen(token->str) == 1 && token->str[0] == '~')
	{
		free(token->str);
		token->str = ft_getenv(data, "HOME");
		return (0);
	}
	while (token->str[i])
	{
		if (token->str[i] == '\'')
			i += (ft_unquote(token, i, '\'') + 2);
		else if (token->str[i] == '"')
			i += ft_dquote(data, token, i);
		else if (token->str[i] == '$' && (ft_isalnum(token->str[i + 1]) == 1
				|| token->str[i + 1] == '_' || token->str[i + 1] == '?') && x)
			i = ft_xsplit(data, token, i);
		else
			i++;
	}
	return (0);
}
