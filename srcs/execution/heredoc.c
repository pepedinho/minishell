/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:21:36 by madamou           #+#    #+#             */
/*   Updated: 2024/08/06 00:36:57 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_parse_line(char *line)
{
	char	*dest;
	char	**envp;
	t_info	*info;

	info = info_in_static(NULL, GET);
	envp = t_env_to_envp(info->env);
	if (!envp)
		handle_malloc_error("heredoc");
	dest = ft_strchr(line, '$');
	if (!dest)
		return (line);
	dest = ft_is_evn_variable(line, envp);
	if (!dest)
		handle_malloc_error("heredoc");
	return (free(line), dest);
}

void	here_doc(t_element *tmp)
{
	char	*line;
	int		fd[2];
	int		save_stdout;
	int		save_stderr;

	if (pipe(fd) == -1)
		error_message("pipe");
	save_stdout = dup(STDOUT_FILENO);
	save_stderr = dup(STDERR_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	close(STDERR_FILENO);
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
			free(line);
			break ;
		}
		line = ft_parse_line(line);
		(write(fd[WRITE], line, ft_strlen(line)), write(fd[WRITE], "\n", 1));
		free(line);
	}
	dup2(save_stdout, STDOUT_FILENO);
	dup2(save_stderr, STDERR_FILENO);
	close(save_stderr);
	(close(save_stdout), close(fd[WRITE]));
	tmp->infile = fd[READ];
}
