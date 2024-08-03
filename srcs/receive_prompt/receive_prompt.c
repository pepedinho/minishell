/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:03:56 by madamou           #+#    #+#             */
/*   Updated: 2024/08/02 22:17:20 by madamou          ###   ########.fr       */
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
	if (g_signal_code == 0)
		prompt = ft_sprintf("\001\033[0;34m\002%s:\001\033[0;32m\002%s\001\033[0m\002$ ",
				hostname, pwd);
	else
		prompt = ft_sprintf("\001\033[0;34m\002%s:\001\033[0;32m\002%s\001\033[0;31m$\001\033[0m\002 ",
				hostname, pwd);
	return (prompt);
}

char	**ready_to_exec(t_element *cmd)
{
	char		**cmd_tab;
	t_element	*current;
	int			i;

	i = 0;
	current = cmd;
	while (current && !is_a_redirect(current->type))
	{
		i++;
		current = current->next;
	}
	current = cmd;
	cmd_tab = ft_malloc(sizeof(char *) * (i + 1));
	if (!cmd_tab)
		return (NULL);
	i = 0;
	while (current && !is_a_redirect(current->type))
	{
		if (current->type == R_RED || current->type == RR_RED
			|| current->type == L_RED || current->type == LL_RED)
		{
			current = current->next->next;
			continue ;
		}
		cmd_tab[i] = current->content;
		current = current->next;
		i++;
	}
	cmd_tab[i] = NULL;
	return (cmd_tab);
}

t_command_line	*change_queue(t_command_line *queue)
{
	t_element	*current;
	t_element	*tmp;

	current = queue->first;
	while (current)
	{
		tmp = current;
		if (current->type == CMD)
		{
			current->args = ready_to_exec(current);
			current = current->next;
			while (current && current->type != PIPE && current->type != AND
				&& current->type != OR && current->type != LIST)
			{
				if (current->type == RR_RED || current->type == R_RED)
				{
					tmp->file_mode = current->type;
					tmp->outfile = current->next->content;
				}
				else if (current->type == L_RED || current->type == LL_RED)
				{
					if (tmp->infile != -1)
						close(tmp->infile);
					tmp->infile = current->next->infile;
				}
				current = current->next;
			}
		}
		if (current)
			current = current->next;
	}
	return (queue);
}

void	queue_add_back(t_command_line **queue, t_command_line *new)
{
	t_command_line	*buff;

	buff = *queue;
	while (buff->next)
		buff = buff->next;
	buff->next = new;
	new->next = NULL;
}

t_command_line	*remove_in_queue(t_command_line *queue)
{
	t_element		*current;
	t_element		*next;
	t_command_line	*tmp_queue;

	current = queue->first;
	while (current)
	{
		next = current->next;
		if (current->type != CMD && current->type != PIPE
			&& current->type != AND && current->type != OR
			&& current->type != LIST && current->type != C_BLOCK)
		{
			if (current->before)
				current->before->next = next;
			else
				queue->first = next;
			if (next)
				next->before = current->before;
		}
		if (current->type == LIST)
		{
			tmp_queue = init_queue();
			if (!tmp_queue)
				handle_malloc_error("queue");
			tmp_queue->first = current->next;
			queue_add_back(&queue, tmp_queue);
			current->before->next = NULL;
		}
		current = next;
	}
	return (queue);
}

void	tree_add_back(t_tree **tree, t_tree *new)
{
	t_tree	*buff;

	if (*tree == NULL)
		*tree = new;
	else
	{
		buff = *tree;
		while (buff->next)
			buff = buff->next;
		buff->next = new;
	}
	new->next = NULL;
}

void	receive_prompt_subminishell(char *command_line, t_info *info)
{
	t_command_line	*queue;
	t_tree			*tree;

	sigaction_signals();
	queue = parser(command_line, info->env);
	// print_queue(queue);
	global_check(queue);
	queue = change_queue(queue);
	queue = remove_in_queue(queue);
	tree = NULL;
	while (queue)
	{
		tree_add_back(&tree, smart_agencement(queue));
		queue = queue->next;
	}
	execute_command_line(tree);
	ft_free(DESTROY);
}

void	if_only_newline(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	receive_prompt(t_info *info)
{
	char			*command_line;
	t_command_line	*queue;
	t_tree			*tree;
	char			*prompt;

	while (1)
	{
		sigaction_signals();
		prompt = get_prompt(info);
		command_line = readline(prompt);
		free(prompt);
		if (!command_line)
		{
			g_signal_code = 0;
			break ;
		}
		if (ft_strcmp(command_line, "\n") == 0)
			if_only_newline();
		queue = parser(command_line, info->env);
		print_queue(queue);
		global_check(queue);
		queue = change_queue(queue);
		queue = remove_in_queue(queue);
		tree = NULL;
		while (queue && queue->first)
		{
			tree_add_back(&tree, smart_agencement(queue));
			queue = queue->next;
		}
		add_history(command_line);
		free(command_line);
		// execute_command_line(tree);
		ft_free(DESTROY);
	}
}
