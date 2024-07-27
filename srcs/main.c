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

extern int	g_signal_code;

void	minishell(t_info *info)
{
	receive_prompt(info);
	ft_printf("exit\n");
	rl_clear_history();
}

void	subminishell(char **argv, t_info *info)
{
	if (ft_strcmp(argv[1], "-c") != 0)
	{
		g_signal_code = 2;
		return ;
	}
	if (argv[3])
		info->name = argv[3];
	receive_prompt_subminishell(argv[2], info);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	sigaction_sigint();
	info.envp = envp;
	info.name = "minishell";
	if (argc == 2)
		minishell(&info);
	else
		subminishell(argv, &info);
	return (g_signal_code);
}
