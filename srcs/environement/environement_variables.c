/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement_variables.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:43:41 by madamou           #+#    #+#             */
/*   Updated: 2024/08/27 15:13:56 by itahri           ###   ########.fr       */
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

char	*ft_getenv(char *key)
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
	if (!tmp)
		return (NULL);
	return (tmp->value);
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
	t_env	*current;

	current = *env;
	if (!(*env))
	{
		*env = new;
		new->next = NULL;
		new->before = NULL;
	}
	else if (search_in_env(new->key))
	{
		current = search_in_env(new->key);
		ft_free(current->value);
		current->value = new->value;
		ft_free(new->key);
		ft_free(new);
	}
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
		new->before = current;
	}
}

t_env	*init_env(char *envp, int cas)
{
	t_env	*new;
	char	**split;

	new = ft_malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	split = split_first_value(envp, '=');
	if (!split)
		return (ft_free(new), NULL);
	new->key = split[0];
	new->value = split[1];
	ft_free(split);
	new->global = cas;
	new->next = NULL;
	new->before = NULL;
	return (new);
}
