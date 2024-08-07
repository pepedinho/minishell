/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 16:30:58 by madamou           #+#    #+#             */
/*   Updated: 2024/08/03 15:06:45 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_env *env, int cas)
{
	while (env && env->global == GLOBAL)
	{
		if (ft_printf("%s", env->key) == -1)
			handle_malloc_error("printf env");
		if (env->value)
		{
			if (cas == 1)
			{
				if (ft_printf("=%s\n", env->value) == -1)
					handle_malloc_error("printf env");
			}
			else if (cas == 2)
			{
				if (ft_printf("=\"%s\"\n", env->value) == -1)
					handle_malloc_error("printf env");
			}
		}
		else
			ft_printf("\n");
		env = env->next;
	}
	g_signal_code = EXIT_SUCCESS;
}

void	env(void)
{
	t_info *info;

	info = info_in_static(NULL, GET);
	print_env(info->env, 1);
	exit(EXIT_SUCCESS);
}