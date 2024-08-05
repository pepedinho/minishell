/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:39:21 by madamou           #+#    #+#             */
/*   Updated: 2024/08/05 19:06:59 by madamou          ###   ########.fr       */
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
		(close(fd[0]), close(fd[1]));
		(exec(node->left, info), exit(info->signal_code));
	}
	pid[1] = ft_fork();
	if (pid[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		(close(fd[0]), close(fd[1]));
		(exec(node->right, info), exit(info->signal_code));
	}
	(close(fd[0]), close(fd[1]));
	(waitpid(pid[0], &status, 0), waitpid(pid[1], &status, 0));
	exit_status(status, info);
}

void and (t_element * node, t_info *info)
{
	int	status;
	int	pid;

	if (check_if_fork(node->left))
	{
		pid = ft_fork();
		if (pid == 0)
			exec(node->left, info);
		(waitpid(pid, &status, 0), exit_status(status, info));
	}
	else
		exec(node->left, info);
	if (info->signal_code == 0)
	{
		if (check_if_fork(node->right))
		{
			pid = ft_fork();
			if (pid == 0)
				exec(node->right, info);
			(waitpid(pid, &status, 0), exit_status(status, info));
		}
		else
			exec(node->right, info);
	}
}

void or (t_element * node, t_info *info)
{
	int	status;
	int	pid;

	if (check_if_fork(node->left))
	{
		pid = ft_fork();
		if (pid == 0)
			exec(node->left, info);
		(waitpid(pid, &status, 0), exit_status(status, info));
	}
	else
		exec(node->left, info);
	if (info->signal_code != 0)
	{
		if (check_if_fork(node->right))
		{
			pid = ft_fork();
			if (pid == 0)
				exec(node->right, info);
			(waitpid(pid, &status, 0), exit_status(status, info));
		}
		else
			exec(node->right, info);
	}
}
