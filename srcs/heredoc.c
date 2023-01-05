#include "minishell.h"

// static char	*here_doc(char *str)
// {
// 	char	*limiter;
// 	char	*line;
// 	char	*input_s;
// 	char	*tmp_input_s;

// 	limiter = ft_strjoin(str, "\n");
// 	write(1, ">", 1);
// 	line = get_next_line(0);
// 	input_s = ft_calloc(ft_strlen(line) + 1, sizeof(char));
// 	while (ft_strncmp(line, limiter, ft_strlen(limiter)))
// 	{
// 		write(1, ">", 1);
// 		tmp_input_s = input_s;
// 		input_s = ft_strjoin(input_s, line);
// 		free(tmp_input_s);
// 		line = get_next_line(0);
// 	}
// 	free(limiter);
// 	return (input_s);
// }

int ft_heredoc(t_data *data, char *str)
{
	(void) data;
	(void) str;
	// t_cmd	*head;

	// here_doc(str);
	// printf("%s", here_doc(str));
	// head = data->cmdlist;
	// while(head->next)
	// {

	// 	head = head->next;
	// }
	return (2);
}
