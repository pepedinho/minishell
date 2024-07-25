/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:43:35 by madamou           #+#    #+#             */
/*   Updated: 2024/07/25 22:08:51 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[])
{
	t_command_line	*queue;
	char			*line;

	(void)argv;
	(void)argc;
	line = readline("minishell > ");
	ft_printf("%s\n", line);
	queue = init_queue();
	if (!queue)
		return (10);
	parser(line, queue);
	print_queue(queue);
	ft_free(DESTROY);
	return (EXIT_SUCCESS);
}
