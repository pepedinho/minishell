/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:50:12 by itahri            #+#    #+#             */
/*   Updated: 2024/07/26 13:35:37 by madamou          ###   ########.fr       */
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

int	add_redirect(t_command_line *queue, char redirection)
{
	char	*str;

	if (!is_a_separator(redirection))
		return (0);
	str = ft_malloc(sizeof(char) * 2);
	if (!str)
		return (0);
	str[0] = redirection;
	str[1] = '\0';
	if (!add_to_queue(queue, str, 3))
		return (0);
	return (1);
}

int	add_elem_for_quotes(t_command_line *queue, char *str, int *i)
{
	int		j;
	char	*cmd;

	j = 1;
	while (str[*i + j] && str[*i + j] != '"')
		j++;
	cmd = ft_malloc(sizeof(char) * (j + 1));
	if (!cmd)
		return (0);
	j = 1;
	while (str[*i + j] && str[*i + j] != '"')
	{
		cmd[j - 1] = str[*i + j];
		j++;
	}
	cmd[j - 1] = '\0';
	if (!add_to_queue(queue, cmd, 1))
		return (0);
	*i += j;
	return (1);
}

int	add_elem(t_command_line *queue, char *str, int *i)
{
	int			j;
	char		*cmd;
	int static	quotes;

	if (quotes == 2)
		quotes = 0;
	j = 0;
	while (str[*i + j] && str[*i + j] != ' ' && !is_a_separator(str[*i + j]))
	{
		if (str[*i + j] == '"')
			quotes++;
		j++;
	}
	if (quotes == 1)
		return (quotes++, add_elem_for_quotes(queue, str, i));
	if (!j)
		return ((*i)++, add_redirect(queue, str[*i + j]));
	cmd = ft_malloc(sizeof(char) * (j + 1));
	if (!cmd)
		return (0);
	j = 0;
	while (str[*i + j] && str[*i + j] != ' ' && !is_a_separator(str[*i + j]))
	{
		cmd[j] = str[*i + j];
		j++;
	}
	cmd[j] = '\0';
	if (!add_to_queue(queue, cmd, 1))
		return (0);
	*i += j;
	return (1);
}

t_command_line	*parser(char *str)
{
	int				i;
	t_command_line	*queue;
	static int		quotes;

	queue = init_queue();
	i = 0;
	while (str[i])
	{
		if (quotes == 2)
			quotes = 0;
		while (str[i] == ' ')
			i++;
		if (!is_a_separator(str[i]) && (str[i] != ' ' || quotes == 1)
			&& quotes <= 2)
		{
			if (str[i] == '"')
				quotes++;
			add_elem(queue, str, &i);
		}
		if (is_a_separator(str[i]))
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
		if (current->type == 1 || current->type == 3)
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
				else if (current->type == 3)
					printf("|             |____[Redirection]\n");
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
