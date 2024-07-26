/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:03:56 by madamou           #+#    #+#             */
/*   Updated: 2024/07/26 15:28:07 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/history.h>
#include <unistd.h>

void receive_prompt(t_command_line *queue)
{
	char *command_line;

	while (true) 
	{
		command_line = readline("minishell > ");
		add_history(command_line);
		if (!command_line)
			break ;
		parser(command_line, queue);
		free(command_line);
		print_queue(queue);
	}
}
