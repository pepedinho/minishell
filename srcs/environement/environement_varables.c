/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement_varables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:43:41 by madamou           #+#    #+#             */
/*   Updated: 2024/08/10 22:32:25 by madamou          ###   ########.fr       */
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
		free(env->value);
		free(env->key);
		free(env);
		env = buff;
	}
	free(env);
}

t_env *search_in_env(char *key)
{
	t_info *info;
	t_env *tmp;

	info = info_in_static(NULL, GET);
	tmp = info->env;
	while (tmp)
	{
		if (ft_strcmp(key, tmp->key) == 0)
			break;
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

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	split = ft_split(envp, "=");
	if (!split)
		return (free(new), NULL);
	new->key = ft_strdup(split[0]);
	if (!new->key)
		return (free(new), ft_free_2d(split), NULL);
	if (split[1])
	{
		new->value = ft_strdup(split[1]);
		if (!new->value)
			return (free(new->value), ft_free_2d(split), free(new), NULL);
	}
	else
		new->value = NULL;
	ft_free_2d(split);
	new->global = cas;
	new->next = NULL;
	return (new);
}

int	ft_env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**t_env_to_envp(t_env *env)
{
	int		len;
	char	**envp;
	int		i;

	i = 0;
	len = ft_env_size(env);
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		handle_malloc_error("envp");
	while (i < len)
	{
		envp[i] = ft_sprintf("%s=%s", env->key, env->value);
		i++;
		env = env->next;
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
			return (free_env(env), NULL);
		add_back_env(&env, new);
		i++;
	}
	return (env);
}
