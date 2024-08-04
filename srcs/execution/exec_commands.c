/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:58:00 by madamou           #+#    #+#             */
/*   Updated: 2024/08/04 17:09:58 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command(t_element *node)
{
	t_info	*info;
	char	*path;
	char	**envp;

	info = info_in_static(NULL, GET);
	envp = t_env_to_envp(info->env);
	if (!envp)
		handle_malloc_error("envp");
	path = find_path(node->content, info);
	if (path == NULL)
		handle_malloc_error("path");
	(infile(node, info), outfile(node, info));
	execve(path, node->args, envp);
	if (errno == 2)
		ft_fprintf(2, "%s: command not found\n", node->content);
	else
		perror(node->content);
	(free(path), ft_free_2d(envp));
	free_and_exit(errno);
}

void	subshell(t_element *node)
{
	t_info	*info;
	char	**args;
	char	**envp;

	info = info_in_static(NULL, GET);
	envp = t_env_to_envp(info->env);
	if (!envp)
		handle_malloc_error("envp");
	args = ft_malloc(sizeof(char *) * 4);
	if (!args)
		handle_malloc_error("subshell");
	args[0] = ft_strdup("minishell");
	args[1] = ft_strdup("-c");
	args[2] = ft_strdup(node->content);
	args[3] = NULL;
	execve("./minishell", args, envp);
	ft_free_2d(args);
	ft_free_2d(envp);
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
	(infile(node, info), outfile(node, info));
	if (ft_strcmp(node->content, "exit") == 0)
		ft_exit(node->args);
	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	exec_built_in(node, info);
	(dup2(save_stdin, STDIN_FILENO), dup2(save_stdout, STDOUT_FILENO));
	(close(save_stdin), close(save_stdout));
}

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
			(waitpid(pid, &status, 0), exit_status(status));
		}
		else
			exec(tree->first);
		tree = tree->next;
	}
	// printf("echo $? == %d\n", WEXITSTATUS(status));
}
