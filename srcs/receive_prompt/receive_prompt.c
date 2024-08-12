/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:03:56 by madamou           #+#    #+#             */
/*   Updated: 2024/08/12 22:20:51 by madamou          ###   ########.fr       */
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

	if (info->env && search_in_env("PWD") && search_in_env("USER"))
	{
		current = search_in_env("PWD");
		pwd = current->value;
		current = search_in_env("USER");
		hostname = current->value;
		if (info->signal_code == 0)
			prompt = ft_sprintf("\001\033[0;34m\002%s:\001\033[0;32m\002%s\001\033[0m\002$ ",
					hostname, pwd);
		else
			prompt = ft_sprintf("\001\033[0;34m\002%s:\001\033[0;32m\002%s\001\033[0;31m$\001\033[0m\002 ",
					hostname, pwd);
		return (prompt);
	}
	return (ft_sprintf("minishell> "));
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
	int			file_mode;
	char		*output;
	int			infile;

	infile = -1;
	output = NULL;
	file_mode = 0;
	current = queue->first;
	while (current)
	{
		while (current && current->type != CMD)
		{
			if (current->type == RR_RED || current->type == R_RED)
			{
				file_mode = current->type;
				output = current->next->content;
			}
			else if (current->type == L_RED || current->type == LL_RED)
			{
				if (infile != -1)
					close(infile);
				infile = current->next->infile;
			}
			current = current->next;
		}
		if (current)
		{
			tmp = current;
			tmp->infile = infile;
			tmp->outfile = output;
			tmp->file_mode = file_mode;
		}
		if (current && current->type == CMD)
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
		if (current->type != CMD && current->type != LOCAL_VAR
			&& current->type != PIPE && current->type != AND
			&& current->type != OR && current->type != LIST
			&& current->type != C_BLOCK)
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

t_command_line	*parsing(char *command_line, t_info *info)
{
	t_command_line	*queue;

	queue = parser(command_line, info->env);
	if (!queue)
		return (NULL);
	print_queue(queue);
	if (global_check(queue, info) == 0)
		return (NULL);
	queue = change_queue(queue);
	queue = remove_in_queue(queue);
	return (queue);
}

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
void	reprompt(void)
{
	// ft_free(DESTROY);
	queue_in_static(NULL, INIT);
}

void	receive_prompt_subminishell(char *command_line, t_info *info)
{
	t_command_line	*queue;
	t_tree			*tree;

	sigaction_signals();
	queue = parsing(command_line, info);
	if (!queue)
		return ;
	tree = NULL;
	tree = ast(queue);
	execute_command_line(tree);
	ft_free(DESTROY);
}

void	if_only_newline(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

char	*ft_readline(t_info *info)
{
	char	*prompt;
	char	*command_line;

	while (1)
	{
		g_sigint_received = 0;
		prompt = get_prompt(info);
		command_line = readline(prompt);
		ft_free(prompt);
		if (!command_line)
			ft_exit(NULL);
		else if (ft_strcmp(command_line, "") == 0)
			(ft_free(command_line));
		else
			break ;
	}
	prompt = ft_malloc(sizeof(char) * (ft_strlen(command_line) + 1));
	if (!prompt)
		handle_malloc_error("readline");
	ft_strcpy(prompt, command_line);
	ft_free(command_line);
	return (prompt);
}

void	receive_prompt(t_info *info)
{
	t_command_line	*queue;
	t_tree			*tree;
	char			*command_line;

	while (1)
	{
		sigaction_signals();
		command_line = ft_readline(info);
		queue = parsing(command_line, info);
		if (!queue)
		{
			reprompt();
			continue ;
		}
		tree = ast(queue);
		execute_command_line(tree);
		reprompt();
	}
}
