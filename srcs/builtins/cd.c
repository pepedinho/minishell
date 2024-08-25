/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:11:50 by madamou           #+#    #+#             */
/*   Updated: 2024/08/25 15:07:52 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

void	change_old_pwd_in_env(char *old_pwd)
{
	t_env	*env;

	env = search_in_env("OLDPWD");
	if (env)
	{
		ft_free(env->value);
		env->value = old_pwd;
	}
}

void	change_pwd_in_env(t_info *info)
{
	char *pwd;
	t_env *env;

	env = search_in_env("PWD");
	pwd = ft_getenv("PWD");
	if (pwd)
	{
		env->value = ft_pwd(GET, info);
		change_old_pwd_in_env(pwd);
	}
	else
		change_old_pwd_in_env(NULL);
}

char  *go_to_home(char *directory, t_info *info)
{
	directory = ft_getenv("HOME");
	if (!directory)
	{
		printf("%s: cd: HOME not set\n", info->name);
		info->signal_code = 1;
	}
	return (directory);
}

char *go_to_oldpwd(char *directory, t_info *info)
{
	directory = ft_getenv("OLDPWD");
	if (!directory)
	{
		printf("%s: cd: OLDPWD not set\n", info->name);
		info->signal_code = 1;
	}
	return (directory);
}

int	ft_cd(char *directory)
{
	t_info	*info;
	char	*message;

	info = info_in_static(NULL, GET);
	info->signal_code = 0;
	if (!directory || !ft_strcmp(directory, "~"))
		directory = go_to_home(directory, info);
	else if (directory && !ft_strcmp(directory, "-"))
		directory = go_to_oldpwd(directory, info);
	if (!directory)
		return (info->signal_code);
	if (chdir(directory) == -1)
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
