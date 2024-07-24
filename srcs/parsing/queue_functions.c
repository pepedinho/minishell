/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:37:28 by itahri            #+#    #+#             */
/*   Updated: 2024/07/24 18:47:29 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_command_line	*init_queue(void)
{
	t_command_line	*new;

	new = ft_malloc(sizeof(t_command_line));
	if (!new)
		return (NULL);
	new->first = NULL;
	return (new);
}

t_element	*add_to_queue(t_command_line *queue, int type, char *content)
{
	t_element	*new;
	t_element	*current;

	new = ft_malloc(sizeof(t_element));
	if (!new)
		return (NULL);
	new->type = type;
	new->content = content;
	if (!queue->first)
		queue->first = NULL;
	else
	{
		current = queue->first;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (new);
}

void	free_queue(t_command_line *queue)
{
	t_element	*current;
	t_element	*next;

	while (current)
	{
		next = current->next;
		ft_free(current->content);
		ft_free(current);
		current = next;
	}
	free(queue);
}
