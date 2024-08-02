/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:58:00 by madamou           #+#    #+#             */
/*   Updated: 2024/08/02 03:44:12 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		free_and_exit();
	return (pid);
}

void	ft_pipe(t_element *node)
{
	int	fd[2];

	if (pipe(fd) == -1)
		free_and_exit();
	if (ft_fork() == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		(close(fd[0]), close(fd[1]));
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
	exit(0);
}

void and (t_element * node)
{
	if (ft_fork() == 0)
		exec(node->left);
	wait(NULL); // handle when the left part fail
	if (ft_fork() == 0)
		exec(node->right);
	wait(NULL);
	exit(0);
}

void or (t_element * node)
{
	if (ft_fork() == 0)
		exec(node->left);
	wait(NULL); // handle when the left part fail
	if (ft_fork() == 0)
		exec(node->right);
	wait(NULL);
	exit(0);
}

void	outfile(t_element *node, t_info *info)
{
	int	outfile;

	outfile = -1;
	if (node->outfile)
	{
		if (node->file_mode == R_RED)
		{
			outfile = open(node->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (outfile == -1)
				error_message(node->outfile);
		}
		else if (node->file_mode == RR_RED)
		{
			outfile = open(node->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (outfile == -1)
				error_message(node->outfile);
		}
	}
	if (outfile != -1)
	{
		if (dup2(outfile, STDOUT_FILENO) == -1)
			ft_fprintf(2, "%s: Error when trying to dup2\n", info->name);
		close(outfile);
	}
}

void	infile(t_element *node, t_info *info)
{
	if (node->infile != -1)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			ft_fprintf(2, "%s: Error when trying to dup2\n", info->name);
		close(node->infile);
	}
}

void	command(t_element *node)
{
	t_info	*info;
	char	*path;
	char	**args;

	info = info_in_static(NULL, GET);
	path = find_path(node->content, info);
	if (!path)
		handle_malloc_error("path");
	args = ft_split(node->args, " ");
	if (!args)
	{
		free(path);
		handle_malloc_error("args");
	}
	infile(node, info);
	outfile(node, info);
	execve(path, args, t_env_to_envp(info->env));
	if (errno == 2)
		ft_fprintf(2, "%s: command not found\n", node->content);
	else
		perror(node->content);
	free(path);
	free_and_exit();
	exit(0);
}

void	exec(t_element *node)
{
	if (node->type == AND)
		and(node);
	if (node->type == OR)
		or (node);
	if (node->type == PIPE)
		ft_pipe(node);
	if (node->type == CMD)
		command(node);
}
