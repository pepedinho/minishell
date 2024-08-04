/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:37:10 by madamou           #+#    #+#             */
/*   Updated: 2024/08/04 15:38:25 by madamou          ###   ########.fr       */
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

char	*find_path(char *command, t_info *info)
{
	t_env	*env;
	int		i;
	char	*path;

	i = 0;
	env = info->env;
	if (access(command, F_OK) == 0)
		return (ft_strdup(command));
	while (env && ft_strcmp(env->key, "PATH"))
		env = env->next;
	if (!env)
		return (ft_strdup(command));
	ft_free_2d(env->split_value);
	env->split_value = split_value(env->value);
	while (env->split_value[i])
	{
		path = ft_sprintf("%s/%s", env->split_value[i], command);
		if (!path)
			handle_malloc_error("path");
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (ft_strdup(command));
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

	pid = fork();
	if (pid == -1)
		free_and_exit(g_signal_code);
	// find the right signal code if fork fail;
	return (pid);
}

void	exec_built_in(t_element *node, t_info *info)
{
	if (ft_strcmp(node->content, "export") == 0)
		g_signal_code = ft_export(info, node->args);
	if (ft_strcmp(node->content, "env") == 0)
		print_env(info->env, 1);
	if (ft_strcmp(node->content, "pwd") == 0)
		ft_pwd(PRINT);
	if (ft_strcmp(node->content, "echo") == 0)
		ft_echo(node->args);
	if (ft_strcmp(node->content, "cd") == 0)
		g_signal_code = ft_cd(node->args[1]);
	if (ft_strcmp(node->content, "exit") == 0)
		ft_exit(node->args);
}
