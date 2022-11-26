#include "minishell.h"

// if there is no node 
	// create new node
// if there are < > >>
	// set fd
// if <<
	// prepare heredoc
// if |
	// create new node

t_cmd *ft_newnode(void)
{
	t_cmd *node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (0);
	node->argv = 0;
	node->path = 0;
	node->infile = 0;
	node->outfile = 1;
	node->next = 0;
	return (node);
}