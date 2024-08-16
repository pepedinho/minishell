/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:14:17 by madamou           #+#    #+#             */
/*   Updated: 2024/08/16 21:46:05 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**split_first_value(char *str, char sep)
{
	int		i;
	int		j;
	char	**result;

	i = 0;
	j = 0;
	result = ft_malloc(sizeof(char *) * 3);
	if (!result)
		handle_malloc_error("export");
	while (str[i] && str[i] != sep)
		i++;
	result[0] = ft_substr(str, 0, i);
	if (str[i] == sep)
	{
		while (str[j + i + 1])
			j++;
	}
	if (j == 0)
		result[1] = NULL;
	else
		result[1] = ft_substr(str, i + 1, j);
	result[2] = NULL;
	return (result);
}

int	add_in_list(t_info *info, char *content)
{
	char	**key;
	t_env	*current;
	t_env	*new;
	int		flag;

	flag = 0;
	current = info->env;
	key = split_first_value(content, '=');
	while (current)
	{
		if (ft_strcmp(key[0], current->key) == 0)
		{
			// print_env(info->env, 1);
			// printf("-------------------------------------------------------\n");
			if (key[1])
			{
				ft_free(current->value);
				current->value = ft_strdup(key[1]);
			}
			current->global = GLOBAL;
			flag = 1;
			// print_env(info->env, 1);
		}
		current = current->next;
	}
	if (flag == 0)
	{
		new = init_env(content, GLOBAL);
		if (!new)
			return (-1);
		add_back_env(&info->env, new);
	}
	(ft_free(key[0]), ft_free(key[1]), ft_free(key));
	return (1);
}

int is_a_good_variable(char *str)
{
	int i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{		
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);		
		i++;
	}
	return (1);
}

int	ft_export(t_info *info, char **content)
{
	int	i;

	i = 1;
	while (content[i])
	{
		if (is_a_good_variable(content[i]))
		{
			if (add_in_list(info, content[i]) == -1)
				return (ERR_MALLOC);
		}
		else
		{
			printf("%s: export: `%s': not a valid identifier\n", info->name, content[i]);
			info->signal_code = 1;
		}
		i++;
	}
	if (i == 1)
		print_env(info->env, 2, info);
	return (0);
}
