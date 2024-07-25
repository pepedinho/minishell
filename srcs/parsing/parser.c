/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:50:12 by itahri            #+#    #+#             */
/*   Updated: 2024/07/25 21:44:59 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_a_separator(char c)
{
	static int	quotes;

	if (quotes == 2)
		quotes = 0;
	if (c == '"')
		quotes++;
	if (quotes != 1 && (c == '>' || c == '<' || c == '|' || c == '&'
			|| c == ';'))
		return (1);
	return (0);
}

int	add_elem(t_command_line *queue, char *str, int i)
{
	int		j;
	char	*cmd;

	j = 0;
	while (str[i + j] && str[i + j] != ' ' && !is_a_separator(str[i + j]))
		j++;
	if (!j)
		return (1);
	cmd = ft_malloc(sizeof(char) * (j + 1));
	if (!cmd)
		return (0);
	j = 0;
	while (str[i + j] && str[i + j] != ' ' && !is_a_separator(str[i + j]))
	{
		cmd[j] = str[i + j];
		j++;
	}
	cmd[j] = '\0';
	if (!add_to_queue(queue, cmd))
		return (0);
	return (1);
}

void	parser(char **str, t_command_line *queue)
{
	int	i;
	int	j;

	i = 1;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			while (str[i][j] == ' ')
				j++;
			add_elem(queue, str[i], j);
			while (str[i][j] && str[i][j] != ' ')
				j++;
			if (is_a_separator(str[i][j]) || str[i][j] != '\0')
				j++;
		}
		i++;
	}
}

void	print_queue(t_command_line *queue)
{
	t_element	*current;
	int			i;

	i = 0;
	current = queue->first;
	while (current)
	{
		printf("|\n");
		printf("|__[%d]\n", i);
		printf("|    |___[content] -> ['%s']\n", current->content);
		printf("|    |___[type] -> [%d]\n", current->type);
		if (current->type)
		{
			if (current->type == 1)
				printf("|             |__[Command]\n");
		}
		i++;
		current = current->next;
	}
}

