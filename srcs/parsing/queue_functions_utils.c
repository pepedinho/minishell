/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_functions_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:41:45 by itahri            #+#    #+#             */
/*   Updated: 2024/08/27 17:36:10 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
