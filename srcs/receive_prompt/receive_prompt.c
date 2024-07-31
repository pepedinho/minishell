/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:03:56 by madamou           #+#    #+#             */
/*   Updated: 2024/07/31 21:54:27 by madamou          ###   ########.fr       */
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

char	*get_prompt(t_info *info)
{
	t_env	*current;
	char	*pwd;
	char	*hostname;
	char	*prompt;

	current = info->env;
	while (current && ft_strcmp(current->key, "PWD"))
		current = current->next;
	pwd = current->value;
	current = info->env;
	while (current && ft_strcmp(current->key, "USER"))
		current = current->next;
	hostname = current->value;
	prompt = ft_sprintf("\033[0;34m%s:\033[0;32m%s$\033[0m", hostname, pwd);
	return (prompt);
}

void	receive_prompt(t_info *info)
{
	char			*command_line;
	t_command_line	*queue;
	t_tree			*tree;
	char			*prompt;

	while (1)
	{
		prompt = get_prompt(info);
		command_line = readline(prompt);
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
		free(prompt);
		ft_free(DESTROY);
	}
}
