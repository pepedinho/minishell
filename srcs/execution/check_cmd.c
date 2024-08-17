/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 05:38:12 by madamou           #+#    #+#             */
/*   Updated: 2024/08/17 14:35:45 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

int	file(t_element *tmp)
{
	if (tmp->before && tmp->before->type == L_RED)
	{
		tmp->infile = open(tmp->content, O_RDONLY);
		if (tmp->infile == -1)
		{
			error_message(tmp->content);
			return (0);
		}
	}
	return (1);
}

int	open_file(t_command_line *queue, t_info *info)
{
	t_element	*tmp;
	int			i;
	int			j;

	i = 0;
	j = 0;
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
	tmp = queue->first;
	if (!tmp)
		return (0);
	if (tmp->type == PIPE || tmp->type == AND || tmp->type == OR)
	{
		handle_unexpected_token(tmp->content, 2);
		return (0);
	}
	tmp = queue->last;
	if (tmp->type == PIPE || tmp->type == AND || tmp->type == OR || tmp->type == L_RED || tmp->type == LL_RED || tmp->type == R_RED || tmp->type == RR_RED)
	{
		handle_unexpected_token(tmp->content, 2);
		return (0);
	}
	tmp = queue->first;
	while (tmp)
	{
		if (tmp->type == C_BLOCK)
		{
			if (tmp->content[0] == '\0')
			{
				ft_printf("%s: syntax error near unexpected token `)'\n",
							info->name);
				queue->u_token_flag = 1;
				tmp->type = U_TOKEN;
			}
		}
		tmp = tmp->next;
	}
	tmp = queue->first;
	if (queue->u_token_flag == 1)
	{
		while (tmp && tmp->type != U_TOKEN)
		{
			tmp = tmp->next;
			i++;
		}
		if (tmp && tmp->content[0])
			handle_unexpected_token(tmp->content, 1);
	}
	tmp = queue->first;
	while (tmp)
	{
		if (tmp->type == H_FILE)
		{
			if (j <= i)
				here_doc(tmp);
			else
				return (0);
			if (g_signal != 0)
				return (0);
		}
		tmp = tmp->next;
		if (queue->u_token_flag == 1)
			j++;
	}
	tmp = queue->first;
	if (queue->u_token_flag == 1)
		return (0);
	while (tmp)
	{
		if (tmp->type == FILE)
		{
			if (file(tmp) == 0)
			{
				while (tmp && !is_a_redirect(tmp->type))
				{
					tmp = tmp->next;
					if (tmp && tmp->type == AND)
						tmp = tmp->next;
				}
				if (tmp)
					queue->first = tmp->next;
				else
					queue->first = NULL;
			}
		}
		if (tmp)
			tmp = tmp->next;
	}
	return (1);
}

int	global_check(t_command_line *queue, t_info *info)
{
	if (!open_file(queue, info))
		return (0);
	return (1);
}
