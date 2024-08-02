/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:14:17 by madamou           #+#    #+#             */
/*   Updated: 2024/08/02 17:27:47 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void export_the_variable(char *export, t_env *env)
// {
// 	char *key;
// 	char value;
// 	int i;

// 	i = 0;
// 	while (export[i] && export[i] != '=')
// 		i++;
// 	if (export[i])
// 	{
// 		key = export;

// 	}
// 	while (env && ft_strcmp(env->key, export) != 0)
// 		env = env->next;
// 	if (env)
// 	{

// 	}
// }

// void export(char *args)
// {
// 	t_info *info;
// 	char *export;
// 	int i;
// 	int j;

// 	i = 0;
// 	info = info_in_static(NULL, GET);
// 	if (args == NULL)
// 		print_env(info->env, 2);
// 	while (args[i])
// 	{
// 		skip_white_space(args, &i);
// 		j = 0;
// 		while (args[i + j] && args[i + j] != ' ')
// 			j++;
// 		export = ft_substr(args, i, j);
// 		if (!export)
// 			handle_malloc_error("export");

// 	}
// }