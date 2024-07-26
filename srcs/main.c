/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:43:35 by madamou           #+#    #+#             */
/*   Updated: 2024/07/26 16:44:08 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>

int	main(void)
{
	t_command_line	*queue;

	sigaction_sigint();
	queue = init_queue();
	if (!queue)
		return (10);
	receive_prompt(queue);
	ft_printf("exit\n");
	ft_free(DESTROY);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
