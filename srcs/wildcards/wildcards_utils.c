/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 03:06:40 by madamou           #+#    #+#             */
/*   Updated: 2024/08/25 03:08:36 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_strncmp_reverse(char *s1, char *s2, size_t len_s2)
{
	int len;

	len = ft_strlen(s1);
	while (len && len_s2)
	{
		if (s1[len] != s2[len_s2])
			return (s1[len] - s2[len_s2]);
		len--;
		len_s2--;
	}
	return (s1[len] - s2[len_s2]);
}

void add_back_wcards(t_wcards **wcards, t_wcards *new)
{
	t_wcards	*current;
	current = *wcards;
	if (!(*wcards))
	{
		*wcards = new;
		new->next = NULL;
		new->before = NULL;
	}
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
		new->before = current;
	}
}

void create_node_wcards(t_wcards **wcards, char *str, int i, int j)
{
	t_wcards *new;
	new = ft_malloc(sizeof(t_wcards));
	if (!new)
		handle_malloc_error("wildcards");
	new->content = ft_substr(str, i, j);
	new->content[j] = '\0';
	new->before = NULL;
	new->next = NULL;
	add_back_wcards(wcards, new);
}

void skip_quote_wcards(char *str, int i, int *j)
{
	if (str[i + *j] == '"')
	{
		(*j)++;
		while (str[i + *j] != '"')
			(*j)++;
	}
	else if (str[i + *j] == '"')
	{
		(*j)++;
		while (str[i + *j] != '"')
			(*j)++;
	}	
}
