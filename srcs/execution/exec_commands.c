/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:58:00 by madamou           #+#    #+#             */
/*   Updated: 2024/09/13 03:02:32 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command(t_element *node, t_info *info, t_element *first)
{
	char	*path;
	char	**envp;

	(infile(node, info, first), outfile(node, info));
	envp = t_env_to_envp(info->env, GLOBAL);
	if (!envp)
		handle_malloc_error("envp");
	path = find_path(node->content, info);
	if (path == NULL)
	{
		ft_fprintf(2, "%s: %s: command not found\n", info->name, node->args[0]);
		free_and_exit(127);
	}
	if (!ft_strcmp(node->args[0], "ls") || !ft_strcmp(node->args[0], "grep"))
		add_string_char_2d(&node->args, ft_strdup("--color=auto"));
	execve(path, node->args, envp);
	ft_fprintf(2, "%s: Permission denied\n", node->args[0]);
	free_and_exit(126);
}

void	subshell(t_element *node, t_info *info, t_element *first)
{
	char	**args;
	char	**envp;

	envp = t_env_to_envp(info->env, GLOBAL);
	if (!envp)
		handle_malloc_error("envp");
	args = ft_malloc(sizeof(char *) * 4);
	if (!args)
		handle_malloc_error("subshell");
	args[0] = ft_strdup("minishell");
	args[1] = ft_strdup("-c");
	args[2] = ft_strdup(node->content);
	args[3] = NULL;
	(infile(node, info, first), outfile(node, info));
	execve("/tmp/minishell", args, envp);
	ft_fprintf(2, "%s: %s: command not found\n", info->name, node->args[0]);
	free_and_exit(126);
}

void	local_var(t_element *node, t_info *info, t_element *first)
{
	t_env	*new;

	node->content = ft_parse_line(node->content);
	if (!node->content)
		handle_malloc_error("local variable");
	new = init_env(node->content, LOCAL);
	if (!new)
		handle_malloc_error("local variable");
	add_back_env(&info->env, new);
	close_file_tree(first);
	info->signal_code = 0;
}

void	exec(t_element *node, t_info *info, t_element *first)
{
	if (node->type == N_CMD)
	{
		(infile(node, info, first), outfile(node, info));
		free_and_exit(EXIT_SUCCESS);
	}
	if (node->type == LOCAL_VAR)
		local_var(node, info, first);
	if (node->type == AND)
		_and(node, info, first);
	if (node->type == OR)
		_or(node, info, first);
	if (node->type == PIPE)
		ft_pipe(node, info, first);
	if (node->type == C_BLOCK)
		subshell(node, info, first);
	if (node->type == CMD && check_built_in(node->content))
		only_builtin(node, info, first);
	if (node->type == CMD && !check_built_in(node->content))
		command(node, info, first);
}

void	only_builtin(t_element *node, t_info *info, t_element *first)
{
	int	save_stdin;
	int	save_stdout;

	save_stdin = dup(STDIN_FILENO);
	save_stdout = dup(STDOUT_FILENO);
	if (!infile(node, info, first) || !outfile(node, info))
	{
		(ft_close(save_stdin), ft_close(save_stdout));
		return ;
	}
	exec_built_in(node, info);
	if (ft_strcmp(node->content, "exit") == 0)
	{
		(dup2(save_stdin, STDIN_FILENO), dup2(save_stdout, STDOUT_FILENO));
		(ft_close(save_stdin), ft_close(save_stdout));
		ft_exit(node->args);
	}
	else
	{
		(dup2(save_stdin, STDIN_FILENO), dup2(save_stdout, STDOUT_FILENO));
		(ft_close(save_stdin), ft_close(save_stdout));
	}
}
