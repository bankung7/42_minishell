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
		free(prompt);
		if (!data->line)
			return (-1);
		if (ft_strlen(data->line) == 0)
			continue ;
		if (ft_lexical(data) == 0)
			if (ft_parser(data) == 0)
			{
                // ft_ttoken(data);
				// ft_tast(data);
				ft_execute(data);
			}
		ft_clean(data, 0);
		add_history(data->line);
		free(data->line);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	g_status = 0;
	ft_initenv(&data, env);
	ft_sighandle();
	ft_prompt(&data);
	ft_exit(&data, 0);
	return (0);
}
