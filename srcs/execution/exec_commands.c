/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:58:00 by madamou           #+#    #+#             */
/*   Updated: 2024/08/02 19:42:19 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		free_and_exit(g_signal_code);
	// find the right signal code if fork fail;
	return (pid);
}

void	ft_pipe(t_element *node)
{
	int	fd[2];
	int	status;
	int pid[2];

	if (pipe(fd) == -1)
		free_and_exit(g_signal_code);
	pid[0] = ft_fork();
	if (pid[0] == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		(close(fd[0]), close(fd[1]));
		exec(node->left);
	}
	pid[1] = ft_fork();
	if (pid[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		(close(fd[0]), close(fd[1]));
		exec(node->right);
	}
	(close(fd[0]), close(fd[1]));
	(waitpid(pid[0], &status, 0), waitpid(pid[1], &status, 0));
	exit(WEXITSTATUS(status));
}

void and (t_element * node)
{
	int	status;
	int	pid;

	pid = ft_fork();
	if (pid == 0)
		exec(node->left);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 0)
	{
		pid = ft_fork();
		if (pid == 0)
			exec(node->right);
		waitpid(pid, &status, 0);
	}
	exit(WEXITSTATUS(status));
}

void or (t_element * node)
{
	int	status;
	int	pid;

	pid = ft_fork();
	if (pid == 0)
		exec(node->left);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) != 0)
	{
		pid = ft_fork();
		if (pid == 0)
			exec(node->right);
		waitpid(pid, &status, 0);
	}
	exit(WEXITSTATUS(status));
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

	info = info_in_static(NULL, GET);
	path = find_path(node->content, info);
	if (!path)
		handle_malloc_error("path");
	(infile(node, info), outfile(node, info));
	execve(path, node->args, t_env_to_envp(info->env));
	if (errno == 2)
		ft_fprintf(2, "%s: command not found\n", node->content);
	else
		perror(node->content);
	free(path);
	free_and_exit(errno);
}


void subshell(t_element *node)
{
	t_info *info;
	char *argv;
	char **args;
	char **split;

	info = info_in_static(NULL, GET);
	printf("oui\n");
	argv = ft_sprintf("%s %s", "./minishell", "-c");
	if (!argv)
		handle_malloc_error("subshell");
	printf("non\n");
	split = ft_split(argv, " ");
	if (!split)
		(free(argv), handle_malloc_error("subshell"));
	printf("oui\n");
	args = ft_malloc(sizeof(char *) * 4);
	if (!args)
		handle_malloc_error("subshell");
	ft_memset(args, 0, 4);
	(ft_strcpy(args[0], split[0]), ft_strcpy(args[1], split[1]));
	(ft_strcpy(args[2], node->content), ft_free_2d(split));
	args[3] = NULL;
	int i = 0;
	while (args[i])
		printf("%s\n", args[i++]);
	execve("./minishell", args, t_env_to_envp(info->env));
	free_and_exit(errno);
}

void	exec(t_element *node)
{
	restore_sigint();
	if (node->type == AND)
		and(node);
	if (node->type == OR)
		or (node);
	if (node->type == PIPE)
		ft_pipe(node);
	if (node->type == C_BLOCK)
		subshell(node);
	if (node->type == CMD)
		command(node);
}

void	execute_command_line(t_tree *tree)
{
	int	status;
	int	pid;

	pid = ft_fork();
	if (pid == 0)
	{
		while (tree)
		{
			pid = ft_fork();
			if (pid == 0)
				exec(tree->first);
			waitpid(pid, &status, 0);
			tree = tree->next;
		}
		exit(WEXITSTATUS(status));
	}
	waitpid(pid, &status, 0);
	printf("echo $? == %d\n", WEXITSTATUS(status));
	g_signal_code = WEXITSTATUS(status);
}
