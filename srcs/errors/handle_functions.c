/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:25:05 by madamou           #+#    #+#             */
/*   Updated: 2024/08/11 14:54:02 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "errors.h"
#include <sys/types.h>
#include <unistd.h>

void	init_index(char token, int *i)
{
	if (token == '<')
		*i = 3;
	else if (token == ';')
		*i = 1;
	else if (token == '&')
		*i = 2;
	else if (token == '|')
		*i = 2;
	else if (token == '>')
		*i = 2;
}

void	handle_unexpected_token(char *token, int cas)
{
	t_info	*info;
	int		i;
	int		j;

	i = 0;
	j = 0;
	info = info_in_static(NULL, GET);
	init_index(token[0], &i);
	ft_fprintf(2, "%s: syntax error near unexpected token `", info->name);
	if (cas == 1)
	{
		while (token[i + j] && j < 3)
			write(2, &token[i + j++], 1);
	}
	if (cas == 2)
	{
		i = 0;
		while (token[i + j] && j < 2)
			write(2, &token[i + j++], 1);
	}
	write(2, "'\n", 2);
	info->signal_code = 2;
}

void	handle_malloc_error(char *message)
{
	t_info	*info;

	info = info_in_static(NULL, GET);
	ft_fprintf(2, "%s: Error ft_malloc when allocate for %s\n", info->name,
			message);
	info->signal_code = ERR_MALLOC;
	free_and_exit(info->signal_code);
}

void	close_fd(t_command_line *queue)
{
	t_element	*buff;

	if (queue)
	{
		buff = queue->first;
		while (buff)
		{
			if (buff->infile != -1)
				close(buff->infile);
			buff = buff->next;
		}
	}
}

void	free_and_exit(int status_code)
{
	// t_info			*info;
	t_command_line	*queue;

	// info = info_in_static(NULL, GET);
	queue = queue_in_static(NULL, GET);
	close_fd(queue);
	// free_env(info->env);
	ft_free(DESTROY);
	exit(status_code);
}
