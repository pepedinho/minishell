/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:39:21 by madamou           #+#    #+#             */
/*   Updated: 2024/09/09 22:59:21 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pipe(t_element *node, t_info *info, t_element *first)
{
	int	fd[2];
	int	status;
	int	pid[2];

	info = info_in_static(NULL, GET);
	if (pipe(fd) == -1)
		free_and_exit(info->signal_code);
	pid[0] = ft_fork(info);
	if (pid[0] == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		(ft_close(fd[0]), ft_close(fd[1]));
		(exec(node->left, info, first), free_and_exit(info->signal_code));
	}
	pid[1] = ft_fork(info);
	if (pid[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		(ft_close(fd[0]), ft_close(fd[1]));
		(exec(node->right, info, first), free_and_exit(info->signal_code));
	}
	(ft_close(fd[0]), ft_close(fd[1]));
	close_file_tree(first);
	(waitpid(pid[0], &status, 0), exit_status(status, info));
	(waitpid(pid[1], &status, 0), exit_status(status, info));
}

void	fork_because_mandatory(t_element *node, t_info *info, t_element *first)
{
	int	pid;
	int	status;

	pid = ft_fork(info);
	if (pid == 0)
		exec(node, info, first);
	(waitpid(pid, &status, 0), exit_status(status, info));
}

void	_and(t_element *node, t_info *info, t_element *first)
{
	if (check_if_fork(node->left))
		fork_because_mandatory(node->left, info, first);
	else
		exec(node->left, info, first);
	if (info->signal_code == 0 && info->signal_code != 128 + SIGINT
		&& info->signal_code != 128 + SIGQUIT)
	{
		if (check_if_fork(node->right))
			fork_because_mandatory(node->right, info, first);
		else
			exec(node->right, info, first);
	}
	if (node != first)
		close_file_tree(first);
}

void	_or(t_element *node, t_info *info, t_element *first)
{
	if (check_if_fork(node->left))
		fork_because_mandatory(node->left, info, first);
	else
		exec(node->left, info, first);
	if (info->signal_code == 128 + SIGQUIT && info->is_child == 0)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		info->signaled = 0;
	}
	if (info->signal_code != 0 && info->signal_code != 128 + SIGINT)
	{
		if (info->is_child == 1 && info->signal_code == 128 + SIGQUIT)
		{
			if (node != first)
				close_file_tree(first);
			return ;
		}
		if (check_if_fork(node->right))
			fork_because_mandatory(node->right, info, first);
		else
			exec(node->right, info, first);
	}
	if (node != first)
		close_file_tree(first);
}
