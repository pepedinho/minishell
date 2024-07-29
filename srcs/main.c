/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:43:35 by madamou           #+#    #+#             */
/*   Updated: 2024/07/29 02:31:48 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_signal_code = 0;

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
		ft_fprintf(STDERR_FILENO, "minishell: %s: invalid option\n", argv[1]);
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
	if (argc == 1)
		minishell(&info);
	else
		subminishell(argv, &info);
	return (g_signal_code);
}
