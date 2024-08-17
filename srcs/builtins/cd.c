/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:11:50 by madamou           #+#    #+#             */
/*   Updated: 2024/08/17 13:27:50 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

void	change_old_pwd_in_env(t_info *info, char *old_pwd)
{
	t_env	*env;

	env = info->env;
	while (env && ft_strcmp(env->key, "OLDPWD") != 0)
		env = env->next;
	if (env)
	{
		ft_free(env->value);
		env->value = old_pwd;
	}
}

void	change_pwd_in_env(t_info *info)
{
	t_env	*env;
	char	*pwd;

	env = info->env;
	while (env && ft_strcmp(env->key, "PWD") != 0)
		env = env->next;
	if (env)
	{
		pwd = env->value;
		env->value = ft_pwd(GET, info);
		change_old_pwd_in_env(info, pwd);
	}
	else
		change_old_pwd_in_env(info, "");
}

int	ft_cd(char *directory)
{
	t_info	*info;
	char	*message;

	info = info_in_static(NULL, GET);
	info->signal_code = 0;
	if (!directory)
		directory = getenv("HOME");
	if (!directory || chdir(directory) == -1)
	{
		message = ft_sprintf("%s: cd: %s", info->name, directory);
		if (!message)
			handle_malloc_error("cd");
		perror(message);
		ft_free(message);
		info->signal_code = 1;
	}
	if (info->signal_code == 0)
		change_pwd_in_env(info);
	return (info->signal_code);
}
