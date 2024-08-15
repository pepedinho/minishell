/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:43:35 by madamou           #+#    #+#             */
/*   Updated: 2024/08/15 18:45:15 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "environement/env.h"
#include "receive_prompt/prompt.h"

volatile sig_atomic_t	g_signal = 0;

t_info	*info_in_static(t_info *info, int cas)
{
	static t_info	*save;

	if (cas == INIT)
		save = info;
	return (save);
}

void	minishell(t_info *info, char **envp)
{
	info_in_static(info, INIT);
	info->env = env_in_struct(envp);
	pprint_header();
	receive_prompt(info);
	ft_printf("exit\n");
	rl_clear_history();
	return ;
	ft_printf("%s: Error ft_malloc with Environement variables\n", info->name);
	info->signal_code = 105;
}

void	subminishell(char **argv, t_info *info, char **envp)
{
	info_in_static(info, INIT);
	if (ft_strcmp(argv[1], "-c") != 0)
	{
		info->signal_code = 2;
		ft_fprintf(STDERR_FILENO, "minishell: %s: invalid option\n", argv[1]);
		return ;
	}
	if (argv[3])
		info->name = argv[3];
	info->env = env_in_struct(envp);
	if (!info->env)
	{
		ft_printf("%s: Error ft_malloc with Environement variables\n",
					info->name);
		info->signal_code = 105;
		return ;
	}
	receive_prompt_subminishell(argv[2], info);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;

	sigaction_signals(SIGINT, handle_signal_parent);
	sigaction_signals(SIGQUIT, handle_signal_parent);
	sigaction_signals(SIGCHLD, sigchld_handler);
	info.signal_code = 0;
	info.name = "minishell";
	info.env = NULL;
	if (argc == 1)
		minishell(&info, envp);
	else
		subminishell(argv, &info, envp);
	return (info.signal_code);
}
