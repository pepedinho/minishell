/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_prompt_utils3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:35:04 by itahri            #+#    #+#             */
/*   Updated: 2024/09/06 17:27:23 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prompt.h"

t_tree	*ast(t_command_line *queue)
{
	t_tree	*tree;

	tree = NULL;
	while (queue && queue->first)
	{
		tree_add_back(&tree, smart_agencement(queue));
		queue = queue->next;
	}
	return (tree);
}

void	receive_prompt_subminishell(char *command_line, t_info *info)
{
	t_command_line	*queue;
	t_tree			*tree;

	set_signal_parent();
	queue = parsing(command_line, info);
	if (queue)
	{
		tree = ast(queue);
		execute_command_line(tree, info);
	}
	ft_free(DESTROY);
}

char	*ft_readline(t_info *info)
{
	char	*prompt;
	char	*command_line;

	while (1)
	{
		prompt = get_prompt(info);
		command_line = readline(prompt);
		ft_free(prompt);
		if (g_signal != 0)
		{
			set_info_if_signal(info);
			continue ;
		}
		if (!command_line)
			ft_exit(NULL);
		else if (ft_strcmp(command_line, "") == 0)
			ft_free(command_line);
		else
			break ;
	}
	prompt = ft_strdup(command_line);
	return (ft_free(command_line), prompt);
}

void	receive_prompt(t_info *info)
{
	t_command_line	*queue;
	t_tree			*tree;
	char			*command_line;

	while (1)
	{
		set_signal_parent();
		command_line = ft_readline(info);
		queue = parsing(command_line, info);
		if (!queue)
			continue ;
		tree = ast(queue);
		execute_command_line(tree, info);
		if (!isatty(STDOUT_FILENO) ||!isatty(STDIN_FILENO))
			free_and_exit(info->signal_code);
	}
}
