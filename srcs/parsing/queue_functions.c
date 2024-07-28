/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:37:28 by itahri            #+#    #+#             */
/*   Updated: 2024/07/28 21:43:50 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command_line	*init_queue(void)
{
	t_command_line	*new;

	new = ft_malloc(sizeof(t_command_line));
	if (!new)
		return (NULL);
	new->first = NULL;
	return (new);
}

t_element	*add_to_queue(t_command_line *queue, char *content, int type)
{
	t_element	*new;
	t_element	*current;

	new = ft_malloc(sizeof(t_element));
	if (!new)
		return (NULL);
	new->type = type;
	new->content = content;
	new->next = NULL;
	new->before = NULL;
	if (!queue->first)
	{
		queue->first = new;
		queue->last = new;
	}
	else
	{
		current = queue->first;
		while (current->next)
		{
			current = current->next;
		}
		if (type == CMD && (current->type == L_RED || current->type == R_RED))
			new->type = FILE;
		else if (type == CMD && (current->type == CMD || current->type == SFX))
			new->type = SFX;
		new->before = current;
		current->next = new;
		queue->last = new;
	}
	return (new);
}

void	free_queue(t_command_line *queue)
{
	t_element	*current;
	t_element	*next;

	current = queue->first;
	while (current)
	{
		next = current->next;
		ft_free(current->content);
		ft_free(current);
		current = next;
	}
	ft_free(queue);
}
