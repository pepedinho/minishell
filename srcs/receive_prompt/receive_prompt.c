/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:03:56 by madamou           #+#    #+#             */
/*   Updated: 2024/08/26 19:43:50by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
								hostname,
								pwd);
		else
			prompt = ft_sprintf("\001\033[0;34m\002%s:\001\033[0;32m\002%s\001\033[0;31m$\001\033[0m\002 ",
								hostname,
								pwd);
		return (prompt);
	}
	return (ft_sprintf("minishell> "));
}

char	**prepare_args_to_exec(t_element *cmd)
{
	char		**cmd_tab;
	t_element	*current;
	int			i;

	i = 0;
	current = cmd;
	while (current && !is_a_operator(current->type))
	{
		i++;
		current = current->next;
	}
	current = cmd;
	cmd_tab = ft_malloc(sizeof(char *) * (i + 1));
	if (!cmd_tab)
		handle_malloc_error("parsing");
	i = 0;
	while (current && !is_a_operator(current->type))
	{
		if (current->type == SFX || current->type == CMD
			|| current->type == C_BLOCK || current->type == LOCAL_VAR)
			cmd_tab[i++] = current->content;
		current = current->next;
	}
	return (cmd_tab[i] = NULL, cmd_tab);
}

void	add_string_char_2d(char ***tab, char *str)
{
	char	**new;
	int		i;
	char	**buff;

	buff = *tab;
	new = ft_malloc(sizeof(char *) * (ft_strlen_2d(buff) + 1 + 1));
	if (!new)
		handle_malloc_error("pasing");
	i = 0;
	while (buff && buff[i])
	{
		new[i] = buff[i];
		if (!new[i])
			handle_malloc_error("parsing");
		i++;
	}
	new[i] = str;
	if (!new[i])
		handle_malloc_error("parsing");
	new[++i] = NULL;
	ft_free(buff);
	*tab = new;
}

void	add_int_to_tab(int **tab, int nb, char **char_tab)
{
	int	*new;
	int	i;
	int	*buff;

	buff = *tab;
	new = ft_malloc(sizeof(int) * (ft_strlen_2d(char_tab) + 1));
	if (!new)
		handle_malloc_error("pasing");
	i = 0;
	while (char_tab && char_tab[i])
	{
		new[i] = buff[i];
		i++;
	}
	new[i] = nb;
	ft_free(buff);
	*tab = new;
}

void	stock_infile_outfile(t_change *change, t_element **node)
{
	t_element	*current;

	current = *node;
	if (current->type == RR_RED || current->type == R_RED)
	{
		add_int_to_tab(&change->file_mode, current->type, change->output);
		add_string_char_2d(&change->output, current->next->content);
	}
	else if (current->type == L_RED || current->type == LL_RED)
	{
		add_int_to_tab(&change->infile_tab, current->next->fd, change->infile);
		add_string_char_2d(&change->infile, current->next->content);
	}
	current = current->next;
	*node = current;
}

void	change_to_current(t_change *change, t_element **node, t_element **tmp)
{
	t_element	*current;

	current = *node;
	if (!current || (current && is_a_operator(current->type)))
	{
		current = *tmp;
		if (current->type != LOCAL_VAR)
			current->type = N_CMD;
	}
	current->infile = change->infile;
	current->infile_tab = change->infile_tab;
	current->outfile = change->output;
	current->file_mode = change->file_mode;
	if (!current || (current && is_a_operator(current->type)))
		current = current->next;
	*node = current;
}

void	redirections_before_command(t_change *change, t_element **node,
		t_element **tmp)
{
	t_element	*current;

	current = *node;
	while (current && current->type != CMD && current->type != C_BLOCK
		&& !is_a_operator(current->type))
	{
		*tmp = current;
		stock_infile_outfile(change, &current);
	}
	*node = current;
	change_to_current(change, node, tmp);
}

void	redirections_after_command(t_change *change, t_element **node,
		t_element **tmp)
{
	t_element	*current;

	current = *node;
	current->args = prepare_args_to_exec(current);
	*tmp = current;
	while (current && current->type != PIPE && current->type != AND
		&& current->type != OR && current->type != LIST)
		stock_infile_outfile(change, &current);
	*node = current;
	change_to_current(change, tmp, node);
}

t_command_line	*change_queue(t_command_line *queue)
{
	t_element	*current;
	t_element	*tmp;
	t_change	change;

	current = queue->first;
	while (current)
	{
		ft_memset(&change, 0, sizeof(change));
		redirections_before_command(&change, &current, &tmp);
		if (current && (current->type == CMD || current->type == C_BLOCK
				|| current->type == LOCAL_VAR))
			redirections_after_command(&change, &current, &tmp);
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

void	link_before_and_after(t_command_line *queue, t_element **current)
{
	if ((*current)->before)
		(*current)->before->next = (*current)->next;
	else
		queue->first = (*current)->next;
	if ((*current)->next)
		(*current)->next->before = (*current)->before;
}

void	free_current(t_element **current)
{
	t_element	*tmp;

	tmp = (*current)->next;
	ft_free(*current);
	*current = tmp;
}

t_command_line	*remove_in_queue(t_command_line *queue)
{
	t_element		*current;
	t_command_line	*tmp_queue;

	current = queue->first;
	while (current)
	{
		if (current->type != CMD && current->type != LOCAL_VAR
			&& current->type != C_BLOCK && current->type != N_CMD
			&& !is_a_operator(current->type))
			(link_before_and_after(queue, &current), free_current(&current));
		else if (current->type == LIST)
		{
			tmp_queue = init_queue();
			if (!tmp_queue)
				handle_malloc_error("queue");
			tmp_queue->first = current->next;
			queue_add_back(&queue, tmp_queue);
			current->before->next = NULL;
			free_current(&current);
		}
		else
			current = current->next;
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

	queue = parser(command_line);
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

void	receive_prompt_subminishell(char *command_line, t_info *info)
{
	t_command_line	*queue;
	t_tree			*tree;

	set_signal_parent();
	queue = parsing(command_line, info);
	if (queue)
	{
		tree = ast(queue);
		execute_command_line(tree);
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
		{
			ft_free(command_line);
			info->signal_code = 0;
		}
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
		execute_command_line(tree);
	}
}
