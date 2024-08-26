/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:37:28 by itahri            #+#    #+#             */
/*   Updated: 2024/08/26 18:48:33 by madamou          ###   ########.fr       */
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
	new->next = NULL;
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
	while (tmp && !is_a_redirect(tmp->type))
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

int	check_for_wcards(t_command_line *queue, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"')
				i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
		}
		else if (str[i] == '*')
			return (expand_wcards(str, queue));
		i++;
	}
	return (0);
}

void	if_not_the_first(t_command_line *queue, t_element *new, int type)
{
	t_element	*tmp;
	t_element	*current;

	current = queue->first;
	while (current->next)
		current = current->next;
	if (type == CMD && is_redirection(current))
		new->type = FILE;
	else if (type == CMD && current->type == LL_RED)
	{
		new->type = H_FILE;
		queue->heredoc_flag = 1;
	}
	else if (type == CMD)
	{
		tmp = current;
		check_if_command_before(tmp, new);
	}
	new->before = current;
	current->next = new;
}

int	is_a_redirection(int type)
{
	if (type == RR_RED || type == R_RED)
		return (1);
	if (type == L_RED || type == LL_RED)
		return (1);
	return (0);
}

t_element	*add_to_queue(t_command_line *queue, char *content, int type)
{
	t_element	*new;
	t_element	*current;

	new = create_new_element(type, content);
	if (type == HU_TOKEN)
		queue->u_heredoc_token_flag = 1;
	if (!queue->first)
		queue->first = new;
	else
	{
		current = queue->first;
		while (current->next)
			current = current->next;
		if_not_the_first(queue, new, type);
	}
	queue->last = new;
	if (new->type == CMD && ft_strchr(new->content, '=')
		&& is_a_good_variable(new->content))
		new->type = LOCAL_VAR;
	if (new->type == LIST && is_a_redirection(new->before->type))
	{
		new->type = U_TOKEN;
		queue->u_token_flag = 1;
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

void	free_node_queue(t_element *node)
{
	ft_free(node->content);
	ft_free(node);
	node = NULL;
}
