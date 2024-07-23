/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_queue_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@contact.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:12:38 by itahri            #+#    #+#             */
/*   Updated: 2024/07/23 15:57:11 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collecting.h"

t_garbage	*init_garbage(void)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return (NULL);
	new->first = NULL;
	return (new);
}

t_to_destroy	*push_to_garbage(t_garbage *garbage, void *ptr)
{
	t_to_destroy	*new;
	t_to_destroy	*current;

	new = malloc(sizeof(t_to_destroy));
	if (!new)
		return (NULL);
	if (!garbage->first)
		garbage->first = new;
	else
	{
		current = garbage->first;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	new->to_destroy = ptr;
	new->next = NULL;
	return (new);
}

void	destroy(t_garbage *garbage, t_to_destroy *elem)
{
	t_to_destroy	*current;
	t_to_destroy	*tmp_n;
	t_to_destroy	*tmp_b;

	if (!garbage)
		return ;
	current = garbage->first;
	if (elem == garbage->first->to_destroy)
	{
		garbage->first = current->next;
		(free(current->to_destroy), free(current));
		garbage->first = NULL;
		return ;
	}
	while (current && current->to_destroy != elem)
	{
		tmp_b = current;
		current = current->next;
	}
	if (current->to_destroy == elem)
	{
		tmp_n = current->next;
		(free(current->to_destroy), free(current));
		tmp_b->next = tmp_n;
	}
}

void	destroy_all(t_garbage *garbage)
{
	t_to_destroy	*current;
	t_to_destroy	*next;

	if (!garbage->first)
	{
		free(garbage);
		return ;
	}
	current = garbage->first;
	while (current->next)
	{
		next = current->next;
		free(current->to_destroy);
		free(current);
		current = next;
	}
	free(garbage);
}
