/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:03:56 by madamou           #+#    #+#             */
/*   Updated: 2024/08/18 13:16:55 by madamou          ###   ########.fr       */
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

char	**add_string_char_2d(char **tab, char *str)
{
	char	**new;
	int		i;

	new = ft_malloc(sizeof(char *) * (ft_strlen_2d(tab) + 1 + 1));
	if (!new)
		handle_malloc_error("pasing");
	i = 0;
	while (tab && tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		if (!new[i])
			handle_malloc_error("parsing");
		i++;
	}
	new[i] = ft_strdup(str);
	if (!new[i])
		handle_malloc_error("parsing");
	new[++i] = NULL;
	ft_free_2d(tab);
	ft_free(str);
	return (new);
}

int	*add_int_to_tab(int *tab, int nb, char **char_tab)
{
	int	*new;
	int	i;

	new = ft_malloc(sizeof(int) * (ft_strlen_2d(char_tab) + 1));
	if (!new)
		handle_malloc_error("pasing");
	i = 0;
	while (char_tab && char_tab[i])
	{
		new[i] = tab[i];
		i++;
	}
	new[i] = nb;
	ft_free(tab);
	return (new);
}

t_command_line	*change_queue(t_command_line *queue)
{
	t_element	*current;
	t_element	*tmp;
	int			*file_mode;
	char		**output;
	char			**infile;
	int			*infile_tab;

	current = queue->first;
	while (current)
	{
		infile = NULL;
		infile_tab = NULL;
		output = NULL;
		file_mode = NULL;
		while (current && current->type != CMD && current->type != C_BLOCK && !is_a_redirect(current->type))
		{
			if (current->type == RR_RED || current->type == R_RED)
			{
				file_mode = add_int_to_tab(file_mode, current->type, output);
				output = add_string_char_2d(output, current->next->content);
			}
			else if (current->type == L_RED || current->type == LL_RED)
			{
				if (current->type == L_RED)
				{
					infile_tab = add_int_to_tab(infile_tab, -1, infile);
					infile = add_string_char_2d(infile, current->next->content);
				}
				else
				{
					infile_tab = add_int_to_tab(infile_tab, current->next->pipe, infile);
					infile = add_string_char_2d(infile, current->next->content);
				}
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
		if (current && is_a_redirect(current->type))
		{
			current->before->type = N_CMD;
			current->before->infile = infile;
			current->before->outfile = output;
			current->before->file_mode = file_mode;
		}
		if (current && (current->type == CMD || current->type == C_BLOCK))
		{
			current->args = ready_to_exec(current);
			current = current->next;
			while (current && current->type != PIPE && current->type != AND
				&& current->type != OR && current->type != LIST)
			{
				if (current->type == RR_RED || current->type == R_RED)
				{
					tmp->file_mode = add_int_to_tab(tmp->file_mode,
							current->type, tmp->outfile);
					tmp->outfile = add_string_char_2d(tmp->outfile,
							current->next->content);
				}
				else if (current->type == L_RED || current->type == LL_RED)
				{
					if (current->type == L_RED)
					{
						tmp->infile_tab = add_int_to_tab(tmp->infile_tab, -1, tmp->infile);
						tmp->infile = add_string_char_2d(tmp->infile, current->next->content);
					}
					else
					{
						tmp->infile_tab = add_int_to_tab(tmp->infile_tab, current->next->pipe, tmp->infile);
						tmp->infile = add_string_char_2d(tmp->infile, current->next->content);
					}
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
	t_element		*tmp;
	t_command_line	*tmp_queue;

	current = queue->first;
	while (current)
	{
		if (current->type != CMD && current->type != LOCAL_VAR
			&& current->type != PIPE && current->type != AND
			&& current->type != OR && current->type != LIST
			&& current->type != C_BLOCK && current->type != N_CMD)
		{
			if (current->before)
				current->before->next = current->next;
			else
				queue->first = current->next;
			if (current->next)
				current->next->before = current->before;
			tmp = current->next;
			ft_free(current);
			current = tmp;
		}
		else if (current->type == LIST)
		{
			tmp_queue = init_queue();
			if (!tmp_queue)
				handle_malloc_error("queue");
			tmp_queue->first = current->next;
			queue_add_back(&queue, tmp_queue);
			current->before->next = NULL;
			tmp = current->next;
			ft_free(current);
			current = tmp;
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
	
	info->signal_code = g_signal;
	set_signal_parent();
	queue = parsing(command_line, info);
	if (!queue)
	{
		ft_free(DESTROY);
		return ;
	}
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
		g_signal = 0;
		prompt = get_prompt(info);
		command_line = readline(prompt);
		if (g_signal != 0)
		{
			info->signal_code = g_signal;
			g_signal = 0;
			continue;
		}
		ft_free(prompt);
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
		info->signal_code = g_signal;
		set_signal_parent();
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
