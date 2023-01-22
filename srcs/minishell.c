/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <vnilprap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:04:50 by vnilprap          #+#    #+#             */
/*   Updated: 2023/01/22 21:59:27 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getprompt(void)
{
	char	*cwd;
	char	*prompt;
	char	*tmp;

	cwd = malloc(sizeof(char) * 1024);
	getcwd(cwd, 1023);
	tmp = ft_strjoin(cwd, "$ \e[;37m \e[0m");
	prompt = ft_strjoin("\e[;32m", tmp);
	free(cwd);
	free(tmp);
	return (prompt);
}

int	ft_prompt(t_data *data)
{
	char	*prompt;

	while (1)
	{
		ft_resetdata(data);
		prompt = getprompt();
		data->line = readline(prompt);
		add_history(data->line);
		free(prompt);
		if (!data->line)
			return (-1);
		if (ft_strlen(data->line) == 0)
		{
			free(data->line);
			continue ;
		}
		if (ft_lexical(data) == 0 && ft_parser(data) == 0)
			ft_execute(data);
		ft_clean(data, 0);
		free(data->line);
	}
	return (0);
}

// signal should be new handle
int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	g_status = 0;
	ft_initenv(&data, env);
	ft_sighandle();
	ft_prompt(&data);
	ft_exit(&data, 0, 0);
	return (0);
}
