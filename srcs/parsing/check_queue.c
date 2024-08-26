/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_queue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 05:38:12 by madamou           #+#    #+#             */
/*   Updated: 2024/08/26 22:12:07 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_if_subshell_not_empty(t_command_line *queue, t_info *info)
{
	t_element	*tmp;

	tmp = queue->first;
	while (tmp)
	{
		if (tmp->type == C_BLOCK)
		{
			if (tmp->content[0] == '\0')
			{
				ft_printf("%s: syntax error near unexpected token `)'\n",
					info->name);
				info->signal_code = 2;
				tmp->type = U_TOKEN;
			}
		}
		tmp = tmp->next;
	}
}

void	print_if_find_utoken(t_command_line *queue)
{
	t_element	*tmp;

	tmp = queue->first;
	if (queue->u_token_flag == 1)
	{
		while (tmp && tmp->type != U_TOKEN)
			tmp = tmp->next;
		if (tmp && tmp->content[0])
		{
			if (tmp->content[0] == ';')
				handle_unexpected_token(tmp->content, 2);
			else
				handle_unexpected_token(tmp->content, 1);
		}
	}
}

int	check_cmd(t_command_line *queue, t_info *info)
{
	t_element	*tmp;

	if (check_for_parenthesis(queue, info) == 0)
		return (0);
	if (check_first_and_last_node_queue(queue) == 0)
		return (0);
	check_if_subshell_not_empty(queue, info);
	print_if_find_utoken(queue);
	tmp = queue->first;
	while (tmp)
	{
		if (tmp->type == H_FILE)
		{
			here_doc(tmp);
			if (g_signal != 0)
				return (set_info_if_signal(info), 0);
		}
		if (tmp->type == U_TOKEN)
			return (close_fd(queue), 0);
		tmp = tmp->next;
	}
	return (1);
}

int	global_check(t_command_line *queue, t_info *info)
{
	if (!check_cmd(queue, info))
		return (0);
	return (1);
}
