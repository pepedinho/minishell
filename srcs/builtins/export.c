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

char	**split_first_value(char *str, char sep)
{
	int		i;
	int		j;
	int		k;
	char	**result;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] && str[i] != sep)
		i++;
	while (str[j + i])
		j++;
	result = ft_malloc(sizeof(char *) * 2);
	if (!result)
		return (NULL);
	result[0] = ft_malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	result[1] = ft_malloc(sizeof(char) * (j + 1));
	i = 0;
	j = 0;
	while (str[i] && str[i] != sep)
	{
		result[0][i] = str[i];
		i++;
	}
	result[0][i] = '\0';
	while (str[j + i])
	{
		result[1][j] = str[i + j];
		j++;
	}
	result[1][j] = '\0';
	result[2] = NULL;
	return (result);
}

int	add_in_list(t_info *info, char *content)
{
	char	**key;
	t_env	*current;
	t_env	*new;
	char	*tmp;
	int		flag;

	flag = 0;
	current = info->env;
	key = split_first_value(content, '=');
	if (!key)
		return (-1);
	while (current)
	{
		if (ft_strcmp(key[0], current->key) == 0)
		{
			tmp = current->value;
			current->value = key[1];
			free(current->value);
			flag = 1;
		}
	}
	if (flag == 0)
	{
		new = init_env(content, GLOBAL);
		if (!new)
			return (-1);
	}
	return (1);
}

int	export(t_info *info, char **content)
{
	int	i;

	i = 0;
	return (0);
	while (content[i])
	{
		add_in_list(info, content[i]);
		i++;
	}
}
