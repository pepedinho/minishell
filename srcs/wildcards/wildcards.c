/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:35:50 by itahri            #+#    #+#             */
/*   Updated: 2024/08/27 16:23:57 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_match(char *name, t_wcards *wcards)
{
	if (ft_strcmp(wcards->content, "") != 0)
	{
		if (ft_strncmp(name, wcards->content, ft_strlen(wcards->content)) != 0)
			return (0);
	}
	name = name + ft_strlen(wcards->content);
	wcards = wcards->next;
	while (wcards->next)
	{
		if (ft_strcmp(wcards->content, "") != 0)
		{
			name = ft_strstr(name, wcards->content);
			if (!name)
				return (0);
		}
		wcards = wcards->next;
	}
	if (ft_strcmp(wcards->content, "") != 0)
	{
		if (ft_strncmp_reverse(name, wcards->content,
				ft_strlen(wcards->content)) != 0)
			return (0);
	}
	return (1);
}

t_wcards	*init_wcards(char *str)
{
	t_wcards	*wcards;
	int			i;
	int			j;

	i = 0;
	j = 0;
	wcards = NULL;
	while (str[i + j])
	{
		skip_quote_wcards(str, i, &j);
		if (str[i + j] == '*')
		{
			create_node_wcards(&wcards, str, i, j);
			i += j + 1;
			j = -1;
		}
		j++;
	}
	create_node_wcards(&wcards, str, i, j);
	return (wcards);
}

int	expand_wcards(char *str, t_command_line *queue)
{
	DIR				*current_dir;
	struct dirent	*elem;
	t_wcards		*wcards;
	int				find;

	find = 0;
	wcards = init_wcards(str);
	current_dir = opendir(".");
	elem = readdir(current_dir);
	while (elem)
	{
		if (elem->d_name[0] != '.' && is_match(elem->d_name, wcards))
		{
			add_to_queue(queue, ft_strdup(elem->d_name), CMD);
			find = 1;
		}
		elem = readdir(current_dir);
	}
	closedir(current_dir);
	return (find);
}
