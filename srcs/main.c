/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:43:35 by madamou           #+#    #+#             */
/*   Updated: 2024/08/29 23:44:06 by madamou          ###   ########.fr       */
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

void	set_pwd_and_shlvl(t_info *info)
{
	t_env	*env;

	env = search_in_env("PWD");
	if (!env)
	{
		env = init_env("PWD=", GLOBAL);
		add_back_env(&info->env, env);
	}
	ft_free(env->value);
	env->value = ft_pwd(GET, info);
	env = search_in_env("SHLVL");
	if (!env)
	{
		env = init_env("SHLVL=1", GLOBAL);
		add_back_env(&info->env, env);
	}
	else
	{
		if (ft_is_numeric(env->value) && env->value[0] != '-')
			env->value = ft_sprintf("%d", ft_atoi(env->value) + 1);
		else if (ft_is_numeric(env->value) && env->value[0] == '-')
			env->value = ft_sprintf("%d", 0);
		else
			env->value = ft_sprintf("%d", 1);
	}
}

void	minishell(t_info *info, char **envp)
{
	info->is_child = 0;
	info_in_static(info, INIT);
	info->env = env_in_struct(envp);
	set_pwd_and_shlvl(info);
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
	info->is_child = 1;
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

	info.signal_code = 0;
	info.name = "minishell";
	info.env = NULL;
	if (argc == 1)
		minishell(&info, envp);
	else
		subminishell(argv, &info, envp);
	return (info.signal_code);
}
