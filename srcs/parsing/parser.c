/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:50:12 by itahri            #+#    #+#             */
/*   Updated: 2024/08/15 17:51:44 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "parsing.h"

int	add_redirect(t_command_line *queue, char *str, int *i)
{
	char	*redirection;
	char	symbol;
	int		type;
	int		j;

	symbol = str[*i];
	j = 0;
	while (str[*i + j] == symbol)
		j++;
	redirection = ft_malloc(sizeof(char) * (j + 1));
	if (!redirection)
		handle_malloc_error("redirections");
	j = -1;
	while (str[*i + ++j] == symbol)
		redirection[j] = str[*i + j];
	redirection[j] = '\0';
	type = assigne_type(redirection, queue);
	add_to_queue(queue, redirection, type);
	*i += j;
	return (1);
}

int	add_command(t_command_line *queue, char *str, int *i, t_env *env)
{
	int		j;
	char	*cmd;

	j = 0;
	(void)env;
	while (str[*i + j] && !is_space(str[*i + j]) && !is_a_separator(str[*i + j]))
	{
		if (str[*i + j] == '"')
		{
			j++;
			while (str[*i + j] != '"')
				j++;
		}
		else if (str[*i + j] == '\'')
		{
			j++;
			while (str[*i + j] != '\'')
				j++;
		}
		else if (str[*i + j] == '{')
		{
			j++;
			while (str[*i + j] != '}')
				j++;
		}
		j++;
	}
	cmd = ft_substr(str, *i, j);
	if (!cmd)
		handle_malloc_error("expand variable");
	cmd = expand_if_necessary(cmd);
	if (!cmd[0] && !is_a_quotes(str[*i + j - 1]))
		return (*i += j, 1);
	if (!add_to_queue(queue, cmd, CMD))
		handle_malloc_error("commands");
	*i += j;
	return (1);
}

int	add_elem_for_parenthesis(t_command_line *queue, char *str, int *i)
{
	int		j;
	char	*cmd;
	int		open_parenthesis;
	int		close_parenthesis;

	j = 0;
	open_parenthesis = 1;
	close_parenthesis = 0;
	while (str[*i + ++j])
	{
		if (str[*i + j] == '(')
			open_parenthesis++;
		if (str[*i + j] == '"')
		{
			j++;
			while (str[*i + j] != '"')
				j++;
		}
		if (str[*i + j] == '\'')
		{
			j++;
			while (str[*i + j] != '\'')
				j++;
		}
		if (str[*i + j] == ')')
			close_parenthesis++;
		if (open_parenthesis - close_parenthesis == 0)
			break ;
	}
	if (!str[*i + j] && open_parenthesis - close_parenthesis != 0)
		return (queue->open_parenthesis_flag = 1, *i += j, NO_END_QUOTE);
	cmd = ft_substr(str, *i + 1, j - 1);
	if (!cmd)
		handle_malloc_error("parenthesis");
	if (!add_to_queue(queue, cmd, C_BLOCK))
		handle_malloc_error("env");
	
	return (*i += j + 1, 1);
}

char	*add_elem(t_command_line *queue, char *str, int *i, t_env *env)
{
	if (str[*i] == '(')
		add_elem_for_parenthesis(queue, str, i);
	else if (is_a_separator(str[*i]))
		add_redirect(queue, str, i);
	else
		add_command(queue, str, i, env);
	return (str);
}

t_command_line	*parser(char *str, t_env *env)
{
	int				i;
	t_command_line	*queue;
	char *tmp;

	if (!str[0])
		return (NULL);
	queue = init_queue();
	tmp = ft_strdup(str);
	i = 0;
	str = check_if_command_line_is_good(str, queue);
	if (!str)
		return (add_history(tmp), NULL);
	ft_free(tmp);
	add_history(str);
	while (str[i])
	{
		skip_white_space(str, &i);
		if (str[i])
			str = add_elem(queue, str, &i, env);
	}
	queue = queue_in_static(queue, INIT);
	return (queue);
}

void	print_queue(t_command_line *queue)
{
	t_element	*current;
	int			i;

	i = 0;
	current = queue->first;
	while (current)
	{
		if (current->type != 2)
		{
			printf("|\n");
			printf("|__[%d]\n", i);
			printf("|    |___[content] -> ['%s']\n", current->content);
			printf("|    |___[type] -> [%d]\n", current->type);
			if (current->type)
			{
				if (current->type == 1)
					printf("|             |____[Commands]\n");
				else if (current->type == 2)
					printf("|             |____[Suffix]\n");
				else if (current->type == H_FILE)
					printf("|             |____[Heredoc]\n");
				else if (current->type == C_BLOCK)
					printf("|             |____[Subshell]\n");
				else if (current->type == PIPE)
					printf("|             |____[Pipe]\n");
				else if (current->type == OR)
					printf("|             |____[Or]\n");
				else if (current->type == R_RED)
					printf("|             |____[Right Redirect]\n");
				else if (current->type == RR_RED)
					printf("|             |____[RRight Redirect]\n");
				else if (current->type == L_RED)
					printf("|             |____[Left Redirect]\n");
				else if (current->type == LL_RED)
					printf("|             |____[LLeft Redirect]\n");
				else if (current->type == AND)
					printf("|             |____[And]\n");
				else if (current->type == LIST)
					printf("|             |____[List]\n");
				else if (current->type == FILE)
					printf("|             |____[File]\n");
			}
		}
		else
		{
			printf("|                |\n");
			printf("|                |__[%d]\n", i);
			printf("|                |    |___[content] -> ['%s']\n",
					current->content);
			printf("|                |    |___[type] -> [%d]\n", current->type);
			printf("|                |                    |____[Suffix]\n");
			if (current->type)
			{
			}
		}
		i++;
		current = current->next;
	}
}
