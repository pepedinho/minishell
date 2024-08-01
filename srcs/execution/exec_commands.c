/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:58:00 by madamou           #+#    #+#             */
/*   Updated: 2024/08/01 18:04:15 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_fork()
{
	int pid;

	pid = fork();
	if (pid == -1)
		free_and_exit();
	return (pid);
}

void	exec(t_element *node)
{
	int fd[2];
	t_info *info;

	if (node->type == AND)
	{
		if (ft_fork() == 0)
			exec(node->left);
		wait(NULL); // handle when the left part fail
		if (ft_fork() == 0)
			exec(node->right);
		wait(NULL);
	}
	if (node->type == OR)
	{
		if (ft_fork() == 0)
			exec(node->left);
		wait(NULL); // handle when the left part fail
		if (ft_fork() == 0)
			exec(node->right);
		wait(NULL);
	}
	if (node->type == PIPE)
	{
		if (pipe(fd) == -1)
			free_and_exit();
		if (ft_fork() == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			exec(node->left);
		}
		if (ft_fork() == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);			
			exec(node->right);
		}
		close(fd[0]);
		close(fd[1]);
		wait(NULL);
		wait(NULL);
	}
	if (node->type == CMD)
	{
		info = info_in_static(NULL, GET);
		execve(ft_sprintf("/usr/bin/%s", node->content), ft_split(node->args, " "), t_env_to_envp(info->env));
	}
}
