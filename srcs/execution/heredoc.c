/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 00:21:36 by madamou           #+#    #+#             */
/*   Updated: 2024/08/15 16:25:17 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_bis(t_element *tmp, int *fd)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (g_signal != 0)
			return;
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
	sigaction_signals(SIGINT, change_sigint_heredoc);
	sigaction_signals(SIGQUIT, SIG_IGN);
	heredoc_bis(tmp, fd);
	sigaction_signals(SIGINT, handle_signal_parent);
	sigaction_signals(SIGQUIT, handle_signal_parent);
	(dup2(save[1], STDOUT_FILENO), dup2(save[2], STDERR_FILENO));
	(ft_close(save[1]), ft_close(save[2]), ft_close(fd[WRITE]));
	tmp->infile = fd[READ];
}
