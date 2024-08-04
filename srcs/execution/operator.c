/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:39:21 by madamou           #+#    #+#             */
/*   Updated: 2024/08/04 15:21:52 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pipe(t_element *node)
{
	int	fd[2];
	int	status;
	int	pid[2];

	if (pipe(fd) == -1)
		free_and_exit(g_signal_code);
	pid[0] = ft_fork();
	if (pid[0] == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		(close(fd[0]), close(fd[1]));
		(exec(node->left), exit(g_signal_code));
	}
	pid[1] = ft_fork();
	if (pid[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		(close(fd[0]), close(fd[1]));
		(exec(node->right), exit(g_signal_code));
	}
	(close(fd[0]), close(fd[1]));
	(waitpid(pid[0], &status, 0), waitpid(pid[1], &status, 0));
	exit_status(status);
}

void and (t_element * node)
{
	int	status;
	int	pid;

	if (check_if_fork(node->left))
	{
		pid = ft_fork();
		if (pid == 0)
			exec(node->left);
		(waitpid(pid, &status, 0), exit_status(status));
	}
	else
		exec(node->left);
	if (g_signal_code == 0)
	{
		if (check_if_fork(node->right))
		{
			pid = ft_fork();
			if (pid == 0)
				exec(node->right);
			(waitpid(pid, &status, 0), exit_status(status));
		}
		else
			exec(node->right);
	}
}

void or (t_element * node)
{
	int	status;
	int	pid;

	if (check_if_fork(node->left))
	{
		pid = ft_fork();
		if (pid == 0)
			exec(node->left);
		(waitpid(pid, &status, 0), exit_status(status));
	}
	else
		exec(node->left);
	if (g_signal_code != 0)
	{
		if (check_if_fork(node->right))
		{
			pid = ft_fork();
			if (pid == 0)
				exec(node->right);
			(waitpid(pid, &status, 0), exit_status(status));
		}
		else
			exec(node->right);
	}
}
