/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 05:38:12 by madamou           #+#    #+#             */
/*   Updated: 2024/07/31 21:32:45 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void	message_pipe(char *limiter)
{
	t_info	*info;

	info = info_in_static(NULL, GET);
	ft_printf("%s: warning: here-document at line 1 delimited ", info->name);
	ft_printf("by end-of-file (wanted `%s')\n", limiter);
}

void	here_doc(t_element *tmp)
{
	char	*line;

	if (pipe(tmp->fd) == -1)
		error_message("pipe");
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			message_pipe(tmp->content);
			break ;
		}
		if (ft_strcmp(line, tmp->content) == 0)
		{
			free(line);
			break ;
		}
		write(tmp->fd[WRITE], line, ft_strlen(line));
		write(tmp->fd[WRITE], "\n", 1);
		free(line);
	}
	// close(tmp->fd[WRITE]);
	// tmp->file_fd = tmp->fd[READ];
}

void	file(t_element *tmp)
{
	if (tmp->before && tmp->before->type == L_RED)
	{
		tmp->file_fd = open(tmp->content, O_RDONLY);
		if (tmp->file_fd == -1)
			error_message(tmp->content);
	}
	if (tmp->before && tmp->before->type == R_RED)
	{
		tmp->file_fd = open(tmp->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tmp->file_fd == -1)
			error_message(tmp->content);
	}
	if (tmp->before && tmp->before->type == RR_RED)
	{
		tmp->file_fd = open(tmp->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (tmp->file_fd == -1)
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

void	fill_open_quote(t_element *sfx)
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
			free(line);
			break ;
		}
		len = ft_strlen(sfx->content);
		realloc_str = ft_malloc(sizeof(char) * (len + ft_strlen(line) + 2));
		if (!realloc_str)
			break ;
		i = -1;
		j = 0;
		while (sfx->content[++i])
			realloc_str[i] = sfx->content[i];
		while (line[j])
			realloc_str[i++] = line[j++];
		realloc_str[i] = '\n';
		realloc_str[i + 1] = '\0';
		ft_free(sfx->content);
		sfx->content = realloc_str;
		free(line);
	}
}

int	open_file(t_command_line *queue)
{
	t_element	*tmp;
	int			i;
	int			j;

	i = 0;
	j = 0;
	tmp = queue->first;
	if (queue->open_quotes_flag == 1)
	{
		while (tmp && tmp->type != SFX)
			tmp = tmp->next;
		if (tmp)
			fill_open_quote(tmp);
		print_queue(queue);
	}
	tmp = queue->first;
	if (queue->u_token_flag == 1)
	{
		while (tmp && tmp->type != U_TOKEN)
		{
			tmp = tmp->next;
			i++;
		}
		if (tmp)
			handle_unexpected_token(tmp->content);
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

void	open_pipe(t_command_line *queue)
{
	t_element	*current;

	current = queue->first;
	while (current)
	{
		if (current->type == CMD || current->type == H_FILE)
		{
			if (pipe(current->fd))
				ft_printf("pipe error\n");
		}
		current = current->next;
	}
}

int	global_check(t_command_line *queue, t_tree *tree)
{
	(void)tree;
	if (!open_file(queue))
		return (0);
	open_pipe(queue);
	return (1);
}
