/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:43:35 by madamou           #+#    #+#             */
/*   Updated: 2024/07/27 19:16:32 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "receive_prompt/info.h"

extern int	g_signal_code;

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	sigaction_sigint();
	if (argc == 2)
	{
		info.name = "minishell";
		receive_prompt();
		ft_printf("exit\n");
		rl_clear_history();
	}
	if (argc > 2)
	{
		info.name = argv[3];
	}
	return (g_signal_code);
}
