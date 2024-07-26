/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:43:35 by madamou           #+#    #+#             */
/*   Updated: 2024/07/26 15:14:07 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_command_line	*queue;

	signal(SIGINT, &handle_sigint);
	queue = init_queue();
	if (!queue)
		return (10);
	receive_prompt(queue);
	ft_printf("exit\n");
	ft_free(DESTROY);
	return (EXIT_SUCCESS);
}
