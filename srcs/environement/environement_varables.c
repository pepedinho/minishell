/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement_varables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:43:41 by madamou           #+#    #+#             */
/*   Updated: 2024/08/13 23:18:14 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "env.h"

void	free_env(t_env *env)
{
	t_env	*buff;

	while (env)
	{
		buff = (env)->next;
		ft_free(env->value);
		ft_free(env->key);
		ft_free(env);
		env = buff;
	}
	ft_free(env);
}

t_env	*search_in_env(char *key)
{
	t_info	*info;
	t_env	*tmp;

	info = info_in_static(NULL, GET);
	tmp = info->env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	add_back_env(t_env **env, t_env *new)
{
	t_env	*buff;

	buff = *env;
	if (!(*env))
	{
		*env = new;
		new->next = NULL;
	}
	else if (search_in_env(new->key))
	{
		buff = search_in_env(new->key);
		ft_free(buff->value);
		buff->value = new->value;
		ft_free(new->key);
		ft_free(new);
	}
	else
	{
		while (buff->next)
		{
			buff = buff->next;
		}
		buff->next = new;
	}
}

t_env	*init_env(char *envp, int cas)
{
	t_env	*new;
	char	**split;

	new = ft_malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	split = ft_split(envp, "=");
	if (!split)
		return (ft_free(new), NULL);
	new->key = split[0];
	new->value = split[1];
	ft_free(split);
	new->global = cas;
	new->next = NULL;
	return (new);
}

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
