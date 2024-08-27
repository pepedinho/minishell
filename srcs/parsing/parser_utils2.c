/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:25:04 by itahri            #+#    #+#             */
/*   Updated: 2024/08/27 17:31:22 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	add_cmd_ext(t_command_line *queue, char *str, int *i, int j)
{
	char	*cmd;

	cmd = ft_substr(str, *i, j);
	if (!cmd)
		handle_malloc_error("expand variable");
	if (check_for_wcards(queue, cmd))
		return (*i += j, 1);
	cmd = expand_if_necessary(cmd);
	if (!cmd[0] && !is_a_quotes(str[*i + j - 1]))
		return (*i += j, 1);
	if (!add_to_queue(queue, cmd, CMD))
		handle_malloc_error("commands");
	*i += j;
	return (1);
}

void	continue_until_find(int *i, int *j, char *str, char to_find)
{
	(*j)++;
	while (str[*i + *j] != to_find)
		(*j)++;
}

int	add_command(t_command_line *queue, char *str, int *i)
{
	int	j;

	j = 0;
	while (str[*i + j] && !is_space(str[*i + j]) && !is_a_separator(str[*i
			+ j]))
	{
		if (str[*i + j] == '"')
			continue_until_find(i, &j, str, '"');
		else if (str[*i + j] == '\'')
			continue_until_find(i, &j, str, '\'');
		else if (str[*i + j] == '{')
			continue_until_find(i, &j, str, '}');
		j++;
	}
	return (add_cmd_ext(queue, str, i, j));
}

int	add_prth_ext(t_command_line *queue, char *str, int *i, int j)
{
	char	*cmd;

	cmd = ft_substr(str, *i + 1, j - 1);
	if (!cmd)
		handle_malloc_error("parenthesis");
	if (!add_to_queue(queue, cmd, C_BLOCK))
		handle_malloc_error("env");
	return (*i += j + 1, 1);
}
