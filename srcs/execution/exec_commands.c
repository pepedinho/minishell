/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:58:00 by madamou           #+#    #+#             */
/*   Updated: 2024/08/18 13:07:05 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command(t_element *node, t_info *info, t_element *first)
{
	char	*path;
	char	**envp;

	envp = t_env_to_envp(info->env, GLOBAL);
	if (!envp)
		handle_malloc_error("envp");
	path = find_path(node->content, info);
	if (path == NULL)
		handle_malloc_error("path");
	infile(node, info, first);
	outfile(node, info);
	close_file_tree(first);
	execve(path, node->args, envp);
	if (errno == 2)
	{
		ft_fprintf(2, "%s: command not found\n", node->content);
		free_and_exit(127);
	}
	else
		perror(node->content);
	(ft_free(path), ft_free_2d(envp));
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
	close_file_tree(first);
	execve("./minishell", args, envp);
	ft_free_2d(args);
	ft_free_2d(envp);
	free_and_exit(errno);
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
		free_and_exit(EXIT_SUCCESS);
	if (node->type == LOCAL_VAR)
		local_var(node, info, first);
	if (node->type == AND)
		and(node, info, first);
	if (node->type == OR)
		or (node, info, first);
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
	(infile(node, info, first), outfile(node, info));
	exec_built_in(node, info);
	if (ft_strcmp(node->content, "exit") == 0)
		ft_exit(node->args);
	(dup2(save_stdin, STDIN_FILENO), dup2(save_stdout, STDOUT_FILENO));
	(ft_close(save_stdin), ft_close(save_stdout));
}

void free_tree(t_element *node)
{
	if (!node)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	ft_free_2d(node->args);
	ft_free_2d(node->outfile);
	ft_free(node->infile_tab);
	ft_free(node);
}

void close_file_tree(t_element *current)
{
	int i;

	i = 0;
	if (current->type == CMD || current->type == C_BLOCK || current->type == LOCAL_VAR)
	{
		while (current->infile && current->infile[i])
		{
			ft_close(current->infile_tab[i]);
			i++;
		}
		return;
	}
	close_file_tree(current->left);
	close_file_tree(current->right);
}

void	execute_command_line(t_tree *tree)
{
	int		pid;
	int		status;
	t_tree *tmp;
	t_info	*info;

	info = info_in_static(NULL, GET);
	set_signal_parent_exec();
	while (tree)
	{
		if ((tree->first->type == CMD && !check_built_in(tree->first->content))
			|| tree->first->type == C_BLOCK)
		{
			pid = ft_fork();
			if (pid == 0)
				exec(tree->first, info, tree->first);
			close_file_tree(tree->first);
			(waitpid(pid, &status, 0), exit_status(status, info));
		}
		else
			exec(tree->first, info, tree->first);
		tmp = tree->next;
		free_tree(tree->first);
		ft_free(tree);
		tree = tmp;
	}
}
