/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_prompt_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:34:22 by itahri            #+#    #+#             */
/*   Updated: 2024/08/31 00:09:38 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	link_before_and_after(t_command_line *queue, t_element **current)
{
	if ((*current)->before)
		(*current)->before->next = (*current)->next;
	else
		queue->first = (*current)->next;
	if ((*current)->next)
		(*current)->next->before = (*current)->before;
}

void	free_current(t_element **current)
{
	t_element	*tmp;

	tmp = (*current)->next;
	ft_free(*current);
	*current = tmp;
}

t_command_line	*remove_in_queue(t_command_line *queue)
{
	t_element		*current;
	t_command_line	*tmp_queue;

	current = queue->first;
	while (current)
	{
		if (current->type != CMD && current->type != LOCAL_VAR
			&& current->type != C_BLOCK && current->type != N_CMD
			&& !is_a_operator(current->type))
			(link_before_and_after(queue, &current), free_current(&current));
		else if (current->type == LIST)
		{
			tmp_queue = init_queue();
			if (!tmp_queue)
				handle_malloc_error("queue");
			tmp_queue->first = current->next;
			queue_add_back(&queue, tmp_queue);
			current->before->next = NULL;
			free_current(&current);
		}
		else
			current = current->next;
	}
	return (queue);
}

void	tree_add_back(t_tree **tree, t_tree *new)
{
	t_tree	*buff;

	if (*tree == NULL)
		*tree = new;
	else
	{
		buff = *tree;
		while (buff->next)
			buff = buff->next;
		buff->next = new;
	}
	new->next = NULL;
}

t_command_line	*parsing(char *command_line, t_info *info)
{
	t_command_line	*queue;

	queue = parser(command_line, info);
	if (!queue)
		return (NULL);
	// print_queue(queue);
	if (global_check(queue, info) == 0)
		return (NULL);
	queue = change_queue(queue);
	queue = remove_in_queue(queue);
	return (queue);
}
