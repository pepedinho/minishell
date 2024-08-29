/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:56:32 by itahri            #+#    #+#             */
/*   Updated: 2024/08/29 22:02:54 by madamou          ###   ########.fr       */
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

void	if_potentialy_a_directory(char *command, t_info *info)
{
	struct stat	sb;

	stat(command, &sb);
	if (S_ISDIR(sb.st_mode))
	{
		ft_fprintf(2, "%s: %s: Is a directory\n", info->name, command);
		free_and_exit(126);
	}
	if (ft_access(command) == 0)
		return ;
	if (errno == EACCES)
	{
		ft_fprintf(2, "%s: %s: Permission denied\n", info->name, command);
		free_and_exit(126);
	}
	ft_fprintf(2, "%s: %s: No such file or directory\n", info->name, command);
	free_and_exit(127);
}
