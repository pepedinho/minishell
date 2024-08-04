/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:37:10 by madamou           #+#    #+#             */
/*   Updated: 2024/08/04 14:35:47 by madamou          ###   ########.fr       */
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
	return (0);
}

char	*find_path(char *command, t_info *info)
{
	t_env	*env;
	int		i;
	char	*path;
	char	**tmp;

	i = 0;
	env = info->env;
	if (access(command, F_OK) == 0)
		return (ft_strdup(command));
	while (env && ft_strcmp(env->key, "PATH"))
		env = env->next;
	if (!env)
		return (ft_strdup(command));
	tmp = env->split_value;
	env->split_value = split_value(env->value);
	ft_free_2d(tmp);
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
