/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 09:25:05 by madamou           #+#    #+#             */
/*   Updated: 2024/07/31 19:27:33 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
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

void	handle_unexpected_token(char *token)
{
	t_info	*info;
	int		i;
	int		j;

	i = 0;
	j = 0;
	info = info_in_static(NULL, GET);
	init_index(token[0], &i);
	ft_fprintf(2, "%s: syntax error near unexpected token `", info->name);
	while (token[i + j] && j < 3)
		write(2, &token[i + j++], 1);
	write(2, "'\n", 2);
	g_signal_code = 2;
}

void	handle_malloc_error(char *message)
{
	t_info	*info;

	info = info_in_static(NULL, GET);
	ft_fprintf(2, "%s: Error malloc when allocate for %s\n", info->name,
			message);
	g_signal_code = ERR_MALLOC;
	ft_free(DESTROY);
	exit(g_signal_code);
}

void	close_fd(t_command_line *queue)
{
}

void	free_and_exit(void)
{
	t_info	*info;

	info = info_in_static(NULL, GET);
	free_env(info->env);
	ft_free(DESTROY);
	exit(g_signal_code);
}
