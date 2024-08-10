/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 05:38:12 by madamou           #+#    #+#             */
/*   Updated: 2024/08/06 00:22:07 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void	file(t_element *tmp)
{
	if (tmp->before && tmp->before->type == L_RED)
	{
		tmp->infile = open(tmp->content, O_RDONLY);
		if (tmp->infile == -1)
			error_message(tmp->content);
	}
}

void	unexpected_eof(void)
{
	t_info	*info;

	info = info_in_static(NULL, GET);
	ft_fprintf(2, "%s: unexpected EOF while looking for matching `\"'\n",
			info->name);
}

int	find_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	quote_len(char *line)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (line[i])
	{
		if (line[i] == '"')
			cnt++;
		i++;
	}
	return (i - cnt);
}

char	*fill_open_quote(char *str)
{
	char	*line;
	char	*realloc_str;
	int		len;
	int		i;
	int		j;

	while (1)
	{
		line = readline("dquote> ");
		if (!line)
		{
			unexpected_eof();
			break ;
		}
		if (line[0] == '"')
		{
			realloc_str[i] = '\n';
			realloc_str[i + 1] = '"';
			realloc_str[i + 2] = '\0';
			break ;
		}
		len = ft_strlen(str);
		realloc_str = ft_malloc(sizeof(char) * (len + quote_len(line) + 3));
		if (!realloc_str)
			break ;
		i = -1;
		j = 0;
		while (str[++i])
			realloc_str[i] = str[i];
		while (line[j])
			realloc_str[i++] = line[j++];
		realloc_str[i] = '\n';
		realloc_str[i + 1] = '\0';
		// ft_free(str);
		str = realloc_str;
		if (find_in_str(line, '"'))
		{
			printf("debug fill : %s\n", str);
			realloc_str[i] = '\0';
			break ;
		}
		free(line);
	}
	return (free(line), str);
}

int	open_file(t_command_line *queue)
{
	t_element	*tmp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	tmp = queue->first;
	if (tmp->type == PIPE || tmp->type == AND || tmp->type == OR)
	{
		handle_unexpected_token(tmp->content, 2);
		return (0);
	}
	/*if (queue->open_quotes_flag == 1)
	{
		while (tmp && tmp->type != SFX)
			tmp = tmp->next;
		if (tmp)
			fill_open_quote(tmp);
	}*/
	tmp = queue->first;
	if (queue->u_token_flag == 1)
	{
		while (tmp && tmp->type != U_TOKEN)
		{
			tmp = tmp->next;
			i++;
		}
		if (tmp)
			handle_unexpected_token(tmp->content, 1);
	}
	tmp = queue->first;
	while (tmp)
	{
		if (tmp->type == H_FILE)
		{
			if (j <= i)
				here_doc(tmp);
			else
				return (0);
		}
		tmp = tmp->next;
		if (queue->u_token_flag == 1)
			j++;
	}
	tmp = queue->first;
	while (tmp)
	{
		if (tmp->type == FILE)
			file(tmp);
		tmp = tmp->next;
	}
	return (1);
}

int	global_check(t_command_line *queue)
{
	if (!open_file(queue))
		return (0);
	return (1);
}
