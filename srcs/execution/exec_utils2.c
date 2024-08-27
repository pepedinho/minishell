/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:56:32 by itahri            #+#    #+#             */
/*   Updated: 2024/08/27 14:56:45 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_built_in(t_element *node, t_info *info)
{
	if (ft_strcmp(node->content, "export") == 0)
		info->signal_code = ft_export(info, node->args);
	if (ft_strcmp(node->content, "env") == 0)
		print_env(info->env, 1, info);
	if (ft_strcmp(node->content, "pwd") == 0)
		ft_pwd(PRINT, info);
	if (ft_strcmp(node->content, "echo") == 0)
		ft_echo(node->args, info);
	if (ft_strcmp(node->content, "unset") == 0)
		ft_unset(node->args, info);
	if (ft_strcmp(node->content, "cd") == 0)
		info->signal_code = ft_cd(node->args[1]);
}

void	ft_close(int fd)
{
	if (fd != -1)
	{
		if (close(fd) == -1)
		{
			ft_fprintf(2, "Error close fd number %d\n", fd);
			free_and_exit(-1);
		}
	}
}
