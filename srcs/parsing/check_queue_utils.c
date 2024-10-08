/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_queue_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 03:38:55 by madamou           #+#    #+#             */
/*   Updated: 2024/08/31 00:13:18 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_for_parenthesis(t_command_line *queue, t_info *info)
{
	if (queue->open_parenthesis_flag == 1)
	{
		ft_printf("%s: expected close parenthesis : ')'\n", info->name);
		info->signal_code = 2;
		return (0);
	}
	if (queue->open_parenthesis_flag == 2)
	{
		ft_printf("%s: syntax error near unexpected token `)'\n", info->name);
		info->signal_code = 2;
		return (0);
	}
	return (1);
}

int	check_first_and_last_node_queue(t_command_line *queue)
{
	t_element	*tmp;

	tmp = queue->first;
	if (!tmp)
		return (0);
	if (is_a_operator(tmp->type))
	{
		handle_unexpected_token(tmp->content, 2);
		return (0);
	}
	tmp = queue->last;
	if (tmp->type == PIPE || tmp->type == AND || tmp->type == OR
		|| tmp->type == L_RED || tmp->type == LL_RED || tmp->type == R_RED
		|| tmp->type == RR_RED)
	{
		handle_unexpected_token(tmp->content, 2);
		return (0);
	}
	return (1);
}

int	is_a_operator_redirect(int type)
{
	if (type == PIPE || type == AND || type == OR || type == LIST)
		return (1);
	if (type == LL_RED || type == L_RED || type == R_RED || type == RR_RED)
		return (1);
	return (0);
}
