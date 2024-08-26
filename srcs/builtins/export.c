/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:14:17 by madamou           #+#    #+#             */
/*   Updated: 2024/08/26 22:31:45 by madamou          ###   ########.fr       */
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
		result[1] = ft_malloc(sizeof(char) * (j + 1));
		if (!result[1])
			handle_malloc_error("export");
		ft_strcpy(result[1], &str[i + 1]);
	}
	else
		result[1] = NULL;
	result[2] = NULL;
	return (result);
}

int	add_in_list(t_info *info, char *content)
{
	char	**key;
	t_env	*current;
	t_env	*new;

	key = split_first_value(content, '=');
	current = search_in_env(key[0]);
	if (current)
	{
		if (key[1])
		{
			ft_free(current->value);
			current->value = ft_strdup(key[1]);
		}
		current->global = GLOBAL;
	}
	else 
	{
		new = init_env(content, GLOBAL);
		if (!new)
			return (-1);
		add_back_env(&info->env, new);
	}
	(ft_free(key[0]), ft_free(key[1]), ft_free(key));
	return (1);
}

int	is_a_good_variable(char *str)
{
	int	i;

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
	info->signal_code = 0;
	while (content[i])
	{
		if (is_a_good_variable(content[i]))
		{
			if (add_in_list(info, content[i]) == -1)
				return (ERR_MALLOC);
		}
		else
		{
			printf("%s: export: `%s': not a valid identifier\n", info->name,
				content[i]);
			info->signal_code = 1;
		}
		i++;
	}
	if (i == 1)
		print_env(info->env, 2, info);
	return (info->signal_code);
}
