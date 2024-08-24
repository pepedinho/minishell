/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 05:38:12 by madamou           #+#    #+#             */
/*   Updated: 2024/08/24 05:19:57 by madamou          ###   ########.fr       */
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
		tmp->pipe = open(tmp->content, O_RDONLY);
		if (tmp->pipe == -1)
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
			tmp = tmp->next;
		if (tmp && tmp->content[0])
		{
			if (tmp->content[0] == ';')
				handle_unexpected_token(tmp->content, 2);
			else
				handle_unexpected_token(tmp->content, 1);
		}
	}
	tmp = queue->first;
	while (tmp)
	{
		if (tmp->type == H_FILE)
		{
			here_doc(tmp);
			if (g_signal != 0)
				return (info->signal_code = g_signal, g_signal = 0, 0);
		}
		tmp = tmp->next;
		if (tmp && tmp->type == U_TOKEN)
			return (close_fd(queue), 0);
	}
	return (1);
}

int outfile_open(t_element *tmp)
{
	if (tmp->before && tmp->before->type == R_RED)
	{
		tmp->pipe = open(tmp->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tmp->pipe == -1)
		{
			error_message(tmp->content);
			return (0);
		}
	}
	else if (tmp->before && tmp->before->type == RR_RED)
	{
		tmp->pipe = open(tmp->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (tmp->pipe == -1)
		{
			error_message(tmp->content);
			return (0);
		}
	}
	return (1);
}

int no_need_to_execute(t_command_line *queue)
{
	t_element *current;

	current = queue->first;
	while (current)
	{
		if (current->type == FILE)
		{
			if (file(current) == 0 || outfile_open(current) == 0)
			{
				while (current && (!is_a_redirect(current->type) || current->type == AND))
					current = current->next; // free the element for not stacking allocation
			}
			else
				ft_close(current->pipe);
		}
		if (current)
			current = current->next;
	}
	queue->first = NULL;
	return (1);
}

int	global_check(t_command_line *queue, t_info *info)
{
	int check;
	t_element *current;
	
	current = queue->first;
	check = 0;
	while (current)
	{
		if (current->type == CMD || current->type == C_BLOCK || current->type == LOCAL_VAR)
			check = 1;
		current = current->next;
	}
	if (check == 0)
		return (no_need_to_execute(queue));
	if (!open_file(queue, info))
		return (0);
	return (1);
}
