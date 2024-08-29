/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement_variables_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:07:21 by itahri            #+#    #+#             */
/*   Updated: 2024/08/29 22:25:17 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env_size(t_env *env, int cas)
{
	int	i;

	i = 0;
	if (cas == GLOBAL)
	{
		while (env)
		{
			if (env->global == GLOBAL)
				i++;
			env = env->next;
		}
	}
	if (cas == ALL)
	{
		while (env)
		{
			env = env->next;
			i++;
		}
	}
	return (i);
}

char	**t_env_to_envp(t_env *env, int cas)
{
	int		len;
	char	**envp;
	int		i;

	i = 0;
	len = ft_env_size(env, cas);
	envp = ft_malloc(sizeof(char *) * (len + 1));
	if (!envp)
		handle_malloc_error("envp");
	while (i < len)
	{
		if (cas == GLOBAL && env->global == GLOBAL)
		{
			envp[i++] = ft_sprintf("%s=%s", env->key, env->value);
			env = env->next;
		}
		else if (cas == ALL)
		{
			envp[i++] = ft_sprintf("%s=%s", env->key, env->value);
			env = env->next;
		}
	}
	envp[i] = NULL;
	return (envp);
}

t_env	*env_in_struct(char **envp)
{
	int		i;
	t_env	*env;
	t_env	*new;

	i = 0;
	env = NULL;
	while (envp && envp[i])
	{
		new = init_env(envp[i], GLOBAL);
		if (!new)
			handle_malloc_error("env initilisation");
		add_back_env(&env, new);
		i++;
	}
	return (env);
}
