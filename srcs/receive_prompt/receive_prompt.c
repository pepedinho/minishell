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

void	receive_prompt(void)
{
	char			*command_line;
	t_command_line	*queue;

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
