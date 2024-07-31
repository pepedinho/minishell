/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:43:41 by madamou           #+#    #+#             */
/*   Updated: 2024/07/31 17:40:47 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "env.h"

t_env	*free_env(t_env *env)
{
	t_env	*buff;

	if (!env)
		return (NULL);
	buff = env->next;
	free(env->key);
	free(env->value);
	free(env);
	return (free_env(buff));
}

void	add_back_env(t_env **env, t_env *new)
{
	if (!(*env))
		*env = new;
	else
	{
		while ((*env)->next)
			*env = (*env)->next;
		(*env)->next = new;
	}
	new->next = NULL;
}

t_env	*init_env(char *envp)
{
	t_env	*new;
	char	**split;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	split = ft_split(envp, "=");
	if (!split)
		return (free(new), NULL);
	new->key = split[0];
	new->value = split[1];
	new->next = NULL;
	free(split);
	return (new);
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
		new = init_env(envp[i]);
		if (!new)
			return (free_env(env));
		add_back_env(&env, new);
		i++;
	}
	return (env);
}
