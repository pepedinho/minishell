/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:03:56 by madamou           #+#    #+#             */
/*   Updated: 2024/08/01 17:47:13 by madamou          ###   ########.fr       */
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
	t_element		*tmp;

	(void)info;
	queue = parser(command_line, info->env);
	print_queue(queue);
	smart_agencement(queue);
	if (queue->heredoc_flag == 1)
	{
		tmp = queue->first;
		while (tmp->type != H_FILE)
			tmp = tmp->next;
		message_pipe(tmp->content);
		(ft_free(DESTROY), exit(0));
	}
	global_check(queue);
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
	prompt = ft_sprintf("\033[0;34m%s:\033[0;32m%s\033[0m$ ", hostname, pwd);
	return (prompt);
}

t_command_line *change_queue(t_command_line *queue)
{
	t_element *current;
	t_element *tmp;
	int len;
	char *args;
	
	current = queue->first;
	while (current)
	{
		tmp = current;
		if (current->type == CMD)
		{
			current = current->next;
			while (current && current->type != PIPE && current->type != AND && current->type != OR)
			{
				if (current->type == SFX)
				{
					len = ft_strlen(current->content);
					args = ft_malloc(sizeof(char) * (len + ft_strlen(tmp->args) + 2));
					if (!args)
						handle_malloc_error("queue");
					args[0] = '\0';
					ft_strcpy(args, tmp->args);
					ft_strcat(args, " ");
					ft_strcat(args, current->content);
					tmp->args = args;
				}
				current = current->next;
			}
		}
		if (current)
			current = current->next;	
	}
	return (queue);
}

t_command_line *remove_in_queue(t_command_line *queue)
{
	t_element *current;
	t_element *next;
	t_element *before;

	current = queue->first;
	while (current)
	{
		before = current->before;
		next = current->next;
		if (current->type != CMD && current->type != PIPE && current->type != AND && current->type != OR)	
		{
			before->next = next;
			current = before;
		}
		current = current->next;
	}
	return (queue);
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
		global_check(queue);
		queue = change_queue(queue);
		queue = remove_in_queue(queue);
		tree = smart_agencement(queue);
		add_history(command_line); 
		free(command_line);
		if (ft_fork() == 0)
			exec(tree->first);
		wait(0);
		free(prompt);
		// ft_free(DESTROY);
	}
}
