/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:43:35 by madamou           #+#    #+#             */
/*   Updated: 2024/08/01 21:53:54 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "environement/env.h"
#include "receive_prompt/prompt.h"
#include <stdio.h>

int		g_signal_code = 0;

t_info	*info_in_static(t_info *info, int cas)
{
	static t_info	*save;

	if (cas == INIT)
		save = info;
	return (save);
}

void	minishell(t_info *info, char **envp)
{
	info->env = env_in_struct(envp);
	if (!info->env)
	{
		ft_printf("%s: Error malloc with Environement variables\n",
					info->name);
		g_signal_code = 105;
		return ;
	}
	info_in_static(info, INIT);
	receive_prompt(info);
	ft_printf("exit\n");
	rl_clear_history();
}

void	subminishell(char **argv, t_info *info, char **envp)
{
	if (ft_strcmp(argv[1], "-c") != 0)
	{
		g_signal_code = 2;
		ft_fprintf(STDERR_FILENO, "minishell: %s: invalid option\n", argv[1]);
		return ;
	}
	if (argv[3])
		info->name = argv[3];
	info->env = env_in_struct(envp);
	if (!info->env)
	{
		ft_printf("%s: Error malloc with Environement variables\n",
					info->name);
		g_signal_code = 105;
		return ;
	}
	info_in_static(info, INIT);
	receive_prompt_subminishell(argv[2], info);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	t_env	*buff;

	(void)buff;
	(void)envp;
	sigaction_signals();
	info.name = "minishell";
	if (argc == 1)
		minishell(&info, envp);
	else
		subminishell(argv, &info, envp);
	free_env(info.env);
	return (g_signal_code);
}
