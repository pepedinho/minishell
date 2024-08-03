/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:14:17 by madamou           #+#    #+#             */
/*   Updated: 2024/08/03 15:05:52 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**split_first_value(char *str, char sep)
{
	int		i;
	int		j;
	char	**result;

	i = 0;
	j = 1;
	while (str[i] && str[i] != sep)
		i++;
	while (str[j + i])
		j++;
	result = ft_malloc(sizeof(char *) * 3);
	if (!result)
		return (NULL);
	printf("oui1\n");
	result[0] = ft_malloc(sizeof(char) * (i + 1));
	if (!result[0])
		return (NULL);
	printf("oui2: i = %d j = %d\n", i, j);
	result[1] = ft_malloc(sizeof(char) * (j + 1));
	if (!result[1])
		return (NULL);
	printf("oui3\n");
	i = 0;
	j = 1;
	while (str[i] && str[i] != sep)
	{
		result[0][i] = str[i];
		i++;
	}
	result[0][i] = '\0';
	printf("oui4 : %s\n", result[0]);
	while (str[j + i])
	{
		result[1][j] = str[i + j];
		j++;
	}
	result[1][j] = '\0';
	printf("oui5 : %s\n", result[1]);
	result[2] = NULL;
	i = 0;
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
			print_env(info->env, 1);
			printf("-------------------------------------------------------\n");
			tmp = current->value;
			current->value = key[1];
			free(tmp);
			flag = 1;
			print_env(info->env, 1);
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
	return (1);
}

int	ft_export(t_info *info, char **content)
{
	int	i;

	i = 1;
	while (content[i])
	{
		if (add_in_list(info, content[i]) == -1)
			return (ERR_MALLOC);
		i++;
	}
	if (i == 1)
		print_env(info->env, 2);
	return (0);
}
