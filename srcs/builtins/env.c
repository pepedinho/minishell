/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:30:58 by madamou           #+#    #+#             */
/*   Updated: 2024/08/02 16:55:49 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_env *env, int cas)
{
	if (cas == 1)
	{
		while (env && env->global == GLOBAL)
		{
			if (ft_printf("%s=%s\n", env->key, env->value) == -1)
				handle_malloc_error("printf env");
			env = env->next;
		}
	}
	else if (cas == 2)
	{
		while (env && env->global == GLOBAL)
		{
			if (ft_printf("%s=\"%s\"\n", env->key, env->value) == -1)
				handle_malloc_error("printf env");
			env = env->next;
		}
	}
}

void	env(void)
{
	t_info *info;

	info = info_in_static(NULL, GET);
	print_env(info->env, 1);
	exit(EXIT_SUCCESS);
}