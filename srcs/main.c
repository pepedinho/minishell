/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:43:35 by madamou           #+#    #+#             */
/*   Updated: 2024/07/31 17:21:39 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "environement/env.h"
#include "receive_prompt/prompt.h"

int		g_signal_code = 0;

t_info	*info_in_static(t_info *info, int cas)
{
	static t_info	*save;

	if (cas == INIT)
		save = info;
	return (save);
}

void	minishell(t_info *info)
{
	info_in_static(info, INIT);
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
	info_in_static(info, INIT);
	receive_prompt_subminishell(argv[2], info);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	t_env	*buff;

	sigaction_sigint();
	info.env = env_in_struct(envp);
	if (!info.env)
		return (ft_printf("Error malloc with Environement variables\n"));
	buff = info.env;
	while (buff)
	{
		ft_printf("key = %s\n", buff->key);
		ft_printf("value = %s\n", buff->value);
		buff = buff->next;
	}
	free_env(info.env);
	return (0);
	info.name = "minishell";
	if (argc == 1)
		minishell(&info);
	else
		subminishell(argv, &info);
	return (g_signal_code);
}
