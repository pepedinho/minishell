/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_queue_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:12:38 by itahri            #+#    #+#             */
/*   Updated: 2024/08/10 23:00:40 by madamou          ###   ########.fr       */
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
	new->total_alloc = 0;
	new->total_free = 0;
	return (new);
}

t_to_destroy	*push_to_garbage(t_garbage *garbage, void *ptr)
{
	t_to_destroy	*new;
	t_to_destroy	*current;

	new = malloc(sizeof(t_to_destroy));
	if (!new)
		return (NULL);
	new->to_destroy = ptr;
	new->next = NULL;
	new->before = NULL;
	if (!garbage->first)
		garbage->first = new;
	else
	{
		current = garbage->first;
		while (current->next)
			current = current->next;
		current->next = new;
		new->before = current;
	}
	return (new);
}

int	is_in_garbage(t_garbage *garbage, void *elem)
{
	t_to_destroy	*current;

	current = garbage->first;
	while (current->next)
	{
		if (current->to_destroy == elem)
			return (1);
		current = current->next;
	}
	return (0);
}

void	destroy(t_garbage *garbage, void *elem)
{
	t_to_destroy	*current;

	if (!garbage)
		return ;
	if (!is_in_garbage(garbage, elem))
	{
		// write(STDERR_FILENO, "debug\n", 6);
		free(elem);
		return ;
	}
	current = garbage->first;
	while (current->next && current->to_destroy != elem)
	{
		current = current->next;
	}
	if (current && current->to_destroy == elem)
	{
		if (current->before)
			current->before->next = current->next;
		else
			garbage->first = current->next;
		(free(current->to_destroy), free(current));
	}
}

void	destroy_all(t_garbage *garbage)
{
	t_to_destroy	*current;
	t_to_destroy	*next;

	if (garbage)
	{
		if (!garbage->first)
		{
			free(garbage);
			return ;
		}
		current = garbage->first;
		while (current)
		{
			next = current->next;
			free(current->to_destroy);
			free(current);
			current = next;
		}
	}
	free(garbage);
}
