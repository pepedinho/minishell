/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:11:50 by madamou           #+#    #+#             */
/*   Updated: 2024/08/03 18:11:12 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

void	change_pwd_in_env(t_info *info)
{
	t_env	*env;
	char	*pwd;
	char	*envp;

	env = info->env;
	while (ft_strcmp(env->key, "PWD") != 0)
		env = env->next;
	if (env)
	{
		free(env->value);
		env->value = ft_pwd(GET);
		env->split[1] = env->value;
	}
	else
	{
		pwd = ft_pwd(GET);
		if (!pwd)
			envp = ft_sprintf("PWD=\0");
		else
		{
			envp = ft_sprintf("PWD=%s\0");
			ft_free(pwd);
		}
		if (init_env(envp, GLOBAL))
			handle_malloc_error("cd");
	}
}

int	ft_cd(char *directory)
{
	t_info	*info;
	char	*message;

	info = info_in_static(NULL, GET);
	g_signal_code = 0;
	if (chdir(directory) == -1)
	{
		message = ft_sprintf("%s: %s", info->name, directory);
		if (!message)
			handle_malloc_error("cd");
		perror(message);
		free(message);
		g_signal_code = 1;
	}
	if (g_signal_code == 0)
		change_pwd_in_env(info);
	return (g_signal_code);
}
