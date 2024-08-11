/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:21:36 by madamou           #+#    #+#             */
/*   Updated: 2024/08/11 18:42:07 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_parse_line(char *line)
{
	char	*dest;
	char	**envp;
	t_info	*info;

	info = info_in_static(NULL, GET);
	dest = ft_strchr(line, '$');
	if (!dest)
		return (line);
	envp = t_env_to_envp(info->env, ALL);
	if (!envp)
		handle_malloc_error("heredoc");
	dest = ft_is_evn_variable(line, envp);
	ft_free_2d(envp);
	if (!dest)
		handle_malloc_error("heredoc");
	return (ft_free(line), dest);
}

void	heredoc_bis(t_element *tmp, int *fd)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			message_pipe(tmp->content);
			break ;
		}
		if (ft_strcmp(line, tmp->content) == 0)
		{
			ft_free(line);
			break ;
		}
		line = ft_parse_line(line);
		(write(fd[WRITE], line, ft_strlen(line)), write(fd[WRITE], "\n", 1));
		ft_free(line);
	}
}

void	here_doc(t_element *tmp)
{
	int	fd[2];
	int	save[3];

	if (pipe(fd) == -1)
		error_message("pipe");
	save[1] = dup(STDOUT_FILENO);
	save[2] = dup(STDERR_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	close(STDERR_FILENO);
	heredoc_bis(tmp, fd);
	(dup2(save[1], STDOUT_FILENO), dup2(save[2], STDERR_FILENO));
	(close(save[1]), close(save[2]), close(fd[WRITE]));
	tmp->infile = fd[READ];
}
