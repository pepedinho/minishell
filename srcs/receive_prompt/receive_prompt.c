/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:03:56 by madamou           #+#    #+#             */
/*   Updated: 2024/07/31 19:19:25 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_command_line	*queue_in_static(t_command_line *queue, int cas)
{
	static t_command_line	*save;

	if (cas == INIT)
		save = queue;
	return (save);
}

void	receive_prompt_subminishell(char *command_line, t_info *info)
{
	t_command_line	*queue;
	t_tree			*tree;
	t_element		*tmp;

	(void)info;
	queue = parser(command_line, info->env);
	print_queue(queue);
	tree = smart_agencement(queue);
	if (queue->heredoc_flag == 1)
	{
		tmp = queue->first;
		while (tmp->type != H_FILE)
			tmp = tmp->next;
		message_pipe(tmp->content);
		(ft_free(DESTROY), exit(0));
	}
	global_check(queue, tree);
	ft_free(DESTROY);
}

void	receive_prompt(t_info *info)
{
	char			*command_line;
	t_command_line	*queue;
	t_tree			*tree;

	(void)info;
	while (1)
	{
		command_line = readline("minishell > ");
		if (!command_line)
		{
			g_signal_code = 0;
			break ;
		}
		queue = parser(command_line, info->env);
		print_queue(queue);
		tree = smart_agencement(queue);
		add_history(command_line);
		free(command_line);
		global_check(queue, tree);
		ft_free(DESTROY);
	}
}
