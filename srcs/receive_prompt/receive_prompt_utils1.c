/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_prompt_utils1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:48:10 by madamou           #+#    #+#             */
/*   Updated: 2024/08/29 21:48:14 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

void	change_to_current(t_change *change, t_element **node, t_element **tmp)
{
	t_element	*current;

	current = *node;
	if (!current || (current && is_a_operator(current->type)))
	{
		current = *tmp;
		if (current->type != LOCAL_VAR)
			current->type = N_CMD;
	}
	current->infile = change->infile;
	current->infile_tab = change->infile_tab;
	current->outfile = change->output;
	current->file_mode = change->file_mode;
	if (current->type == N_CMD && current->next
		&& is_a_operator(current->next->type))
		current = current->next;
	*node = current;
}

void	redirections_before_command(t_change *change, t_element **node,
		t_element **tmp)
{
	t_element	*current;

	current = *node;
	while (current && current->type != CMD && current->type != C_BLOCK
		&& !is_a_operator(current->type))
	{
		*tmp = current;
		stock_infile_outfile(change, &current);
	}
	*node = current;
	change_to_current(change, node, tmp);
}

void	redirections_after_command(t_change *change, t_element **node,
		t_element **tmp)
{
	t_element	*current;

	current = *node;
	current->args = prepare_args_to_exec(current);
	*tmp = current;
	while (current && current->type != PIPE && current->type != AND
		&& current->type != OR && current->type != LIST)
		stock_infile_outfile(change, &current);
	*node = current;
	change_to_current(change, tmp, node);
}

t_command_line	*change_queue(t_command_line *queue)
{
	t_element	*current;
	t_element	*tmp;
	t_change	change;

	current = queue->first;
	tmp = NULL;
	while (current)
	{
		ft_memset(&change, 0, sizeof(change));
		redirections_before_command(&change, &current, &tmp);
		if (current && (current->type == CMD || current->type == C_BLOCK
				|| current->type == LOCAL_VAR))
			redirections_after_command(&change, &current, &tmp);
		if (current)
			current = current->next;
	}
	return (queue);
}

void	queue_add_back(t_command_line **queue, t_command_line *new)
{
	t_command_line	*buff;

	buff = *queue;
	while (buff->next)
		buff = buff->next;
	buff->next = new;
	new->next = NULL;
}
