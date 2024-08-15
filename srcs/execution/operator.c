/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:39:21 by madamou           #+#    #+#             */
/*   Updated: 2024/08/15 04:04:06 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pipe(t_element *node, t_info *info)
{
	int	fd[2];
	int	status;
	int	pid[2];

	info = info_in_static(NULL, GET);
	if (pipe(fd) == -1)
		free_and_exit(info->signal_code);
	pid[0] = ft_fork();
	if (pid[0] == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		(ft_close(fd[0]), ft_close(fd[1]));
		(exec(node->left, info), free_and_exit(info->signal_code));
	}
	pid[1] = ft_fork();
	if (pid[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		(ft_close(fd[0]), ft_close(fd[1]));
		(exec(node->right, info), free_and_exit(info->signal_code));
	}
	(ft_close(fd[0]), ft_close(fd[1]));
	(ft_close_infile(node->left), ft_close_infile(node->right));
	(waitpid(pid[0], &status, 0), waitpid(pid[1], &status, 0));
	exit_status(status, info);
}

void	fork_because_mandatory(t_element *node, t_info *info)
{
	int	pid;
	int	status;

	pid = ft_fork();
	if (pid == 0)
		exec(node, info);
	ft_close_infile(node);
	(waitpid(pid, &status, 0), exit_status(status, info));
}

void and (t_element * node, t_info *info)
{
	if (check_if_fork(node->left))
		fork_because_mandatory(node->left, info);
	else
		exec(node->left, info);
	if (info->signal_code == 0)
	{
		if (check_if_fork(node->right))
			fork_because_mandatory(node->right, info);
		else
			exec(node->right, info);
	}
}

void or (t_element * node, t_info *info)
{
	if (check_if_fork(node->left))
		fork_because_mandatory(node->left, info);
	else
		exec(node->left, info);
	if (info->signal_code != 0)
	{
		if (check_if_fork(node->right))
			fork_because_mandatory(node->right, info);
		else
			exec(node->right, info);
	}
}
