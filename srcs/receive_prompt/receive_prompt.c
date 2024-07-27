/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:03:56 by madamou           #+#    #+#             */
/*   Updated: 2024/07/27 19:52:28 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	receive_prompt_subminishell(char *command_line, t_info *info)
{
	t_command_line	*queue;

	(void)info;
	queue = parser(command_line);
	print_queue(queue);
	ft_free(DESTROY);
}

void	receive_prompt(t_info *info)
{
	char			*command_line;
	t_command_line	*queue;

	(void)info;
	while (true)
	{
		command_line = readline("minishell > ");
		if (!command_line)
			break ;
		add_history(command_line);
		queue = parser(command_line);
		free(command_line);
		print_queue(queue);
		ft_free(DESTROY);
	}
}
