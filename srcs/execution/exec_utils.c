/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:37:10 by madamou           #+#    #+#             */
/*   Updated: 2024/08/06 01:25:45 by madamou          ###   ########.fr       */
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
	return (0);
}

char	*find_path(char *command)
{
	int		i;
	char	*path;
	char *envp;
	char **split;

	i = 0;
	if (access(command, F_OK) == 0)
		return (ft_strdup(command));
	envp = getenv("PATH");
	if (!envp)
		return (ft_strdup(command));
	split = ft_split(envp, ":");
	if (!split)
		handle_malloc_error("path");
	while (split[i])
	{
		path = ft_sprintf("%s/%s", split[i], command);
		if (!path)
			(ft_free_2d(split), handle_malloc_error("path"));
		if (access(path, F_OK) == 0)
			return (ft_free_2d(split), path);
		free(path);
		i++;
	}
	return (ft_free_2d(split), ft_strdup(command));
}

int	check_if_fork(t_element *node)
{
	if ((node->type == CMD && !check_built_in(node->content))
		|| node->type == PIPE)
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
	// find the right signal code if fork fail;
	if (pid > 0)
	{
		g_sigint_received = 1;
		sigaction_signals();
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
	if (ft_strcmp(node->content, "cd") == 0)
		info->signal_code = ft_cd(node->args[1]);
}
