/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:37:28 by itahri            #+#    #+#             */
/*   Updated: 2024/09/11 12:54:01 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <time.h>

int	is_a_operator(int type)
{
	if (type == PIPE || type == AND || type == OR || type == LIST)
		return (1);
	return (0);
}

t_command_line	*init_queue(void)
{
	t_command_line	*new;

	new = ft_malloc(sizeof(t_command_line));
	if (!new)
		handle_malloc_error("queues");
	new->first = NULL;
	new->next = NULL;
	new->last = NULL;
	new->heredoc_flag = 0;
	new->u_token_flag = 0;
	new->u_heredoc_token_flag = 0;
	new->open_quotes_flag = 0;
	new->open_parenthesis_flag = 0;
	return (new);
}

t_element	*create_new_element(int type, char *content)
{
	t_element	*new;

	new = ft_malloc(sizeof(t_element));
	if (!new)
		handle_malloc_error("queues");
	new->type = type;
	new->content = content;
	new->next = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->infile_tab = NULL;
	new->file_mode = NULL;
	new->before = NULL;
	new->left = NULL;
	new->right = NULL;
	new->args = NULL;
	new->fd = -1;
	return (new);
}

void	check_if_command_before(t_element *tmp, t_element *new)
{
	while (tmp && !is_a_operator(tmp->type))
	{
		if (tmp->type == CMD)
		{
			new->type = SFX;
			break ;
		}
		else
			new->type = CMD;
		tmp = tmp->before;
	}
}

void	destroy_cmd(t_command_line *queue, t_element *to_destroy)
{
	t_element	*current;
	t_element	*next;

	current = queue->first;
	while (current && current != to_destroy)
	{
		next = current->next;
		current = next;
	}
	if (current)
	{
		if (current->before)
			current->before->next = current->next;
		else
			queue->first = current->next;
		if (current->next)
			current->next->before = current->before;
	}
}
