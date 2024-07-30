/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:03:56 by madamou           #+#    #+#             */
/*   Updated: 2024/07/29 22:47:05 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	receive_prompt_subminishell(char *command_line, t_info *info)
{
	t_command_line	*queue;

	(void)info;
	queue = parser(command_line);
	print_queue(queue);
	smart_agencement(queue);
	ft_free(DESTROY);
}

void	receive_prompt(t_info *info)
{
	char			*command_line;
	t_command_line	*queue;

	(void)info;
	while (1)
	{
		command_line = readline("minishell > ");
		if (!command_line)
			break ;
		queue = parser(command_line);
		print_queue(queue);
		smart_agencement(queue);
		add_history(command_line);
		free(command_line);
		ft_free(DESTROY);
	}
}
