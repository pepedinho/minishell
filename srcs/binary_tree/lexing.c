/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:04:37 by itahri            #+#    #+#             */
/*   Updated: 2024/07/27 19:05:12 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	smart_agencement(t_command_line *queue)
{
	t_element	*current;
	t_element	*before;
	t_element	*tmp;

	current = queue->first;
	while (current)
	{
		before = current;
		current = current->next;
		if (current && current->type / 10 == 3)
		{
			if (current->before == queue->first)
				queue->first = current;
			tmp = current->next;
			current->next = current->before;
			current->before->next = tmp;
		}
	}
}
