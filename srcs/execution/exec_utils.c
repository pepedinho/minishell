/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:37:10 by madamou           #+#    #+#             */
/*   Updated: 2024/08/03 18:24:40 by madamou          ###   ########.fr       */
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

	if (check_built_in(command))
		return (BUILT_IN);
	i = 0;
	env = info->env;
	while (env && ft_strcmp(env->key, "PATH"))
		env = env->next;
	if (!env)
		return (ft_strdup(command));
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
