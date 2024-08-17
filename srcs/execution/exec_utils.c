/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:37:10 by madamou           #+#    #+#             */
/*   Updated: 2024/08/17 16:43:51 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_built_in(char *command)
{
	if (ft_strcmp(command, "export") == 0)
		return (1);
	else if (ft_strcmp(command, "env") == 0)
		return (1);
	else if (ft_strcmp(command, "cd") == 0)
		return (1);
	else if (ft_strcmp(command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(command, "echo") == 0)
		return (1);
	else if (ft_strcmp(command, "exit") == 0)
		return (1);
	else if (ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

int	ft_access(char *path)
{
	int			check_stat;
	struct stat	sb;

	check_stat = stat(path, &sb);
	if (check_stat == -1)
		return (-1);
	if (access(path, F_OK | X_OK) == 0 && S_ISREG(sb.st_mode))
		return (0);
	return (-1);
}

char	*find_path(char *command, t_info *info)
{
	int		i;
	char	*path;
	char	**split;
	t_env	*current;

	i = 0;
	if (ft_access(command) == 0)
		return (command);
	current = info->env;
	while (current && ft_strcmp(current->key, "PATH") != 0)
		current = current->next;
	if (current)
	{
		split = ft_split(current->value, ":");
		while (split[i])
		{
			path = ft_sprintf("%s/%s", split[i], command);
			if (ft_access(path) == 0)
				return (ft_free_2d(split), path);
			(ft_free(path), i++);
		}
		ft_free_2d(split);
	}
	return (command);
}

int	check_if_fork(t_element *node)
{
	if (node->type == LOCAL_VAR)
		return (0);
	if ((node->type == CMD && !check_built_in(node->content))
	 || node->type == C_BLOCK || node->type == N_CMD)
		return (1);
	return (0);
}

int	ft_fork(void)
{
	int	pid;

	kill_if_sigint();
	pid = fork();
	if (pid == -1)
		free_and_exit(-1);
	if (pid == 0)
	{
		g_signal = 1;
		kill_if_sigint();
	}
	if (pid > 0)
	{
		g_signal = 2;
		sigaction_signals(SIGINT, handle_signal_parent);
		sigaction_signals(SIGQUIT, handle_signal_parent);
		sigaction_signals(SIGCHLD, sigchld_handler);
	}
	return (pid);
}

void	exec_built_in(t_element *node, t_info *info)
{
	if (ft_strcmp(node->content, "export") == 0)
		info->signal_code = ft_export(info, node->args);
	if (ft_strcmp(node->content, "env") == 0)
		print_env(info->env, 1, info);
	if (ft_strcmp(node->content, "pwd") == 0)
		ft_pwd(PRINT, info);
	if (ft_strcmp(node->content, "echo") == 0)
		ft_echo(node->args, info);
	if (ft_strcmp(node->content, "unset") == 0)
		ft_unset(node->args, info);
	if (ft_strcmp(node->content, "cd") == 0)
		info->signal_code = ft_cd(node->args[1]);
}

void ft_close_infile(t_element *node)
{
	ft_close(node->infile);
	if (node->type == CMD || node->type == C_BLOCK || node->type == N_CMD)
		return ;
	ft_close_infile(node->left);
	ft_close_infile(node->right);
}

void	ft_close(int fd)
{
	if (fd != -1)
	{
		if (close(fd) == -1)
		{
			ft_fprintf(2, "Error close\n");
			free_and_exit(-1);
		}
	}
}