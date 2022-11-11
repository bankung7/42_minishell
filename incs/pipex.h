/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <pjerddee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 20:01:20 by pjerddee          #+#    #+#             */
/*   Updated: 2022/11/11 21:23:31 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define INFILE		0
# define OUTFILE	1
# define ERR		0
# define FREE		1

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft.h"
// # include "get_next_line.h"

char	**ft_findpath(char **env);
char	*find_bin_path(char *cmd, char **paths);
void	ft_runcmd(char *cmd, char **env, int dupped_fd, int infd);
void	ft_pipex(int argc, char **argv, char **env, int i);
void	ft_err(char *err_msg);
void	ft_free(char **str);

#endif
