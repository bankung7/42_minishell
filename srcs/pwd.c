/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnilprap <vnilprap@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 21:04:51 by vnilprap          #+#    #+#             */
/*   Updated: 2023/01/22 21:04:53 by vnilprap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*str;

	str = ft_calloc(sizeof(char), 1024);
	if (!str)
	{
		g_status = 126;
		return (126);
	}
	if (getcwd(str, 1023) == NULL)
		perror("getcwd() error");
	else
		printf("%s\n", str);
	g_status = 0;
	free(str);
	return (0);
}
