/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <vnilprap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:05:23 by vnilprap          #+#    #+#             */
/*   Updated: 2023/01/22 21:05:23 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Expander split
int	ft_xset(t_expd *stc, t_token *token, int i, t_data *data)
{
	stc->x = -1;
	stc->j = 1;
	while (token->str[i + stc->j] && (ft_isalnum(token->str[i + stc->j]) == 1
			|| token->str[i + stc->j] == '_'))
		stc->j++;
	stc->tmp = ft_substr(token->str, i + 1, stc->j - 1);
	stc->env = ft_getenv(data, stc->tmp);
	return (0);
}

int	ft_xjoin(t_token *token, int i, t_expd *stc)
{
	char	*sub;
	char	*join;

	stc->stmp = ft_split(stc->env, ' ');
	sub = ft_substr(token->str, 0, i);
	join = ft_strjoin(sub, stc->stmp[0]);
	free(stc->stmp[0]);
	stc->stmp[0] = join;
	free(sub);
	return (0);
}

int	ft_xsplit(t_data *data, t_token *token, int i)
{
	t_expd	stc;

	ft_xset(&stc, token, i, data);
	if (ft_strlen(stc.env) == 0)
	{
		free(stc.tmp);
		free(stc.env);
		return (ft_getexpand(data, token, i));
	}
	ft_xjoin(token, i, &stc);
	while (stc.stmp && stc.stmp[++stc.x])
	{
		if (stc.stmp[stc.x + 1] == 0)
		{
			stc.next = ft_substr(token->str, i + stc.j,
					ft_strlen(token->str) - i - stc.j);
			stc.new = ft_strjoin(stc.stmp[stc.x], stc.next);
			ft_freeexpd(&stc);
			free(token->str);
			token->str = stc.new;
		}
		else
			ft_reargv(data, stc.stmp[stc.x]);
	}
	return (ft_free2((void **)stc.stmp, ft_strlen(stc.stmp[stc.x - 1])));
}
