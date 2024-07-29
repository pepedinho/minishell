/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:50:12 by itahri            #+#    #+#             */
/*   Updated: 2024/07/29 04:40:00 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_a_separator(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '&' || c == ';')
		return (1);
	return (0);
}

int	assigne_type(char redirection)
{
	if (redirection == '|')
		return (PIPE);
	if (redirection == '>')
		return (R_RED);
	if (redirection == '<')
		return (L_RED);
	if (redirection == '&')
		return (AND);
	if (redirection == ';')
		return (LIST);
	return (3);
}

int	add_redirect(t_command_line *queue, char redirection)
{
	char	*str;
	int		type;

	str = ft_malloc(sizeof(char) * 2);
	if (!str)
		return (g_signal_code = 105, ERR_MALLOC);
	str[0] = redirection;
	str[1] = '\0';
	type = assigne_type(redirection);
	if (!add_to_queue(queue, str, type))
		return (g_signal_code = 105, ERR_MALLOC);
	return (1);
}

int	add_elem_for_quotes(t_command_line *queue, char *str, int *i)
{
	int		j;
	char	*cmd;

	j = 1;
	while (str[*i + j] && str[*i + j] != '"')
		j++;
	if (!str[*i + j])
		return (NO_END_QUOTE); // handle when quote dosen't end
	cmd = ft_malloc(sizeof(char) * (j + 1));
	if (!cmd)
		return (g_signal_code = 105, ERR_MALLOC);
	j = 1;
	while (str[*i + j] && str[*i + j] != '"')
	{
		cmd[j - 1] = str[*i + j];
		j++;
	}
	cmd[j - 1] = '\0';
	if (!add_to_queue(queue, cmd, 1))
		return (g_signal_code = 105, ERR_MALLOC);
	*i += j;
	return (1);
}

int	add_command(t_command_line *queue, char *str, int *i)
{
	int		j;
	char	*cmd;

	j = 0;
	while (str[*i + j] && str[*i + j] != ' ' && !is_a_separator(str[*i + j]))
		j++;
	cmd = ft_malloc(sizeof(char) * (j + 1));
	if (!cmd)
		return (g_signal_code = 105, ERR_MALLOC);
	j = 0;
	while (str[*i + j] && str[*i + j] != ' ' && !is_a_separator(str[*i + j]))
	{
		cmd[j] = str[*i + j];
		j++;
	}
	cmd[j] = '\0';
	if (!add_to_queue(queue, cmd, 1))
		return (g_signal_code = 105, ERR_MALLOC);
	*i += j;
	return (1);
}

int	add_elem(t_command_line *queue, char *str, int *i)
{
	if (str[*i] == '"')
	{
		if (add_elem_for_quotes(queue, str, i) == ERR_MALLOC)
			free_and_exit(MALLOC_MESS, "quotes");
	}
	else if (is_a_separator(str[*i]))
	{
		if (add_redirect(queue, str[*i]) == ERR_MALLOC)
			free_and_exit(MALLOC_MESS, "redirections");
	}
	else
	{
		if (add_command(queue, str, i) == ERR_MALLOC)
			free_and_exit(MALLOC_MESS, "commands");
	}
	return (1);
}

void	skip_white_space(char *str, int *i)
{
	while (str[*i] == ' ')
		++(*i);
}

t_command_line	*parser(char *str)
{
	int				i;
	t_command_line	*queue;

	queue = init_queue();
	i = 0;
	while (str[i])
	{
		skip_white_space(str, &i);
		add_elem(queue, str, &i);
		if (str[i] != '\0')
			i++;
	}
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
					printf("|             |____[Command]\n");
				else if (current->type == 2)
					printf("|             |____[Suffix]\n");
				else if (current->type == PIPE)
					printf("|             |____[Pipe]\n");
				else if (current->type == R_RED)
					printf("|             |____[Right Redirect]\n");
				else if (current->type == L_RED)
					printf("|             |____[Left Redirect]\n");
				else if (current->type == AND)
					printf("|             |____[And]\n");
				else if (current->type == FILE)
					printf("|             |____[File]\n");
			}
		}
		else
		{
			// printf("|\n");
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
