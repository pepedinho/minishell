/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:58:00 by madamou           #+#    #+#             */
/*   Updated: 2024/08/03 16:19:02 by madamou          ###   ########.fr       */
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
	g_signal_code = WEXITSTATUS(status);
}

int	check_if_fork(t_element *node)
{
	if ((node->type == CMD && !check_built_in(node->content))
		|| node->type == PIPE)
		return (1);
	return (0);
}

void and (t_element * node)
{
	int	status;
	int	pid;

	if (check_built_in(node->left->content))
		only_builtin(node->left);
	else if (check_if_fork(node->left))
	{
		pid = ft_fork();
		if (pid == 0)
			exec(node->left);
		waitpid(pid, &status, 0);
		g_signal_code = WEXITSTATUS(status);
	}
	else
		exec(node->left);
	if (g_signal_code == 0)
	{
		if (check_built_in(node->right->content))
			only_builtin(node->right);
		else if (check_if_fork(node->right))
		{
			pid = ft_fork();
			if (pid == 0)
				exec(node->right);
			waitpid(pid, &status, 0);
			g_signal_code = WEXITSTATUS(status);
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
		waitpid(pid, &status, 0);
		g_signal_code = WEXITSTATUS(status);
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
			waitpid(pid, &status, 0);
			g_signal_code = WEXITSTATUS(status);
		}
		else
			exec(node->right);
	}
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

void	exec_built_in(t_element *node, t_info *info)
{
	if (ft_strcmp(node->content, "export") == 0)
		g_signal_code = ft_export(info, node->args);
	if (ft_strcmp(node->content, "env") == 0)
		print_env(info->env, 1);
	if (ft_strcmp(node->content, "pwd") == 0)
		ft_pwd();
	if (ft_strcmp(node->content, "cd") == 0)
		g_signal_code = ft_cd(node->args[1]);
}

void	command(t_element *node)
{
	t_info	*info;
	char	*path;

	info = info_in_static(NULL, GET);
	path = find_path(node->content, info);
	if (path == NULL)
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

void	subshell(t_element *node)
{
	t_info	*info;
	char	**args;

	info = info_in_static(NULL, GET);
	args = ft_malloc(sizeof(char *) * 4);
	if (!args)
		handle_malloc_error("subshell");
	args[0] = ft_strdup("minishell");
	args[1] = ft_strdup("-c");
	args[2] = ft_strdup(node->content);
	args[3] = NULL;
	execve("./minishell", args, t_env_to_envp(info->env));
	ft_free_2d(args);
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
	if (node->type == CMD && check_built_in(node->content))
		only_builtin(node);
	if (node->type == CMD && !check_built_in(node->content))
		command(node);
}

void	only_builtin(t_element *node)
{
	int		save_stdin;
	int		save_stdout;
	t_info	*info;

	info = info_in_static(NULL, GET);
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	(infile(node, info), outfile(node, info));
	exec_built_in(node, info);
	(dup2(save_stdin, STDIN_FILENO), dup2(save_stdout, STDOUT_FILENO));
}

// TODO: dup2 buit in stdout
void	execute_command_line(t_tree *tree)
{
	int	pid;
	int	status;

	while (tree)
	{
		if (tree->first->type == CMD && !check_built_in(tree->first->content))
		{
			pid = ft_fork();
			if (pid == 0)
				exec(tree->first);
			waitpid(pid, &status, 0);
			g_signal_code = WEXITSTATUS(status);
		}
		else
			exec(tree->first);
		tree = tree->next;
	}
	// printf("echo $? == %d\n", WEXITSTATUS(status));
}
