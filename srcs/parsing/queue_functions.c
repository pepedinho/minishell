/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:37:28 by itahri            #+#    #+#             */
/*   Updated: 2024/07/31 19:45:24 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <time.h>

t_command_line	*init_queue(void)
{
	t_command_line	*new;

	new = ft_malloc(sizeof(t_command_line));
	if (!new)
		handle_malloc_error("queues");
	new->first = NULL;
	new->heredoc_flag = 0;
	new->u_token_flag = 0;
	new->u_heredoc_token_flag = 0;
	new->open_quotes_flag = 0;
	new->open_parenthesis_flag = 0;
	return (new);
}

static int	is_redirection(t_element *elem)
{
	if (elem->type == L_RED || elem->type == R_RED || elem->type == RR_RED)
		return (1);
	return (0);
}

t_element	*add_to_queue(t_command_line *queue, char *content, int type)
{
	t_element	*new;
	t_element	*current;

	new = ft_malloc(sizeof(t_element));
	if (!new)
		handle_malloc_error("queues");
	new->type = type;
	new->content = content;
	new->next = NULL;
	new->path = NULL;
	new->file_fd = -1;
	new->in_output = NULL;
	new->before = NULL;
	if (type == HU_TOKEN)
		queue->u_heredoc_token_flag = 1;
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
		if (type == CMD && is_redirection(current))
			new->type = FILE;
		else if (type == CMD && current->type == LL_RED)
		{
			new->type = H_FILE;
			queue->heredoc_flag = 1;
		}
		else if (type == CMD && (current->type == CMD || current->type == SFX
				|| current->type == H_FILE || current->type == FILE))
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
