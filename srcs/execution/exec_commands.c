/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 23:58:00 by madamou           #+#    #+#             */
/*   Updated: 2024/08/01 00:25:41 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*check_path(t_info *info, char *cmd)
{
	t_env	*env;
	int		i;
	char	*path;

	while (env && ft_strcmp(env->key, "PATH"))
		env = env->next;
	while (env->split[i])
	{
		path = ft_sprintf("%s%s", env->split[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
			return (path);
		ft_free(path);
		i++;
	}
	return (NULL);
}

char	**ready_to_exec(t_element *cmd)
{
	char		**cmd_tab;
	t_element	*current;
	int			i;

	i = 0;
	current = cmd->next;
	while (current && current->type == SFX)
	{
		i++;
		current = current->next;
	}
	current = cmd->next;
	cmd_tab = ft_malloc(sizeof(char *) * (i + 1));
	if (!cmd_tab)
		return (NULL);
	i = 0;
	while (current && current->type == SFX)
	{
		cmd_tab[i] = current->content;
		i++;
	}
	cmd_tab[i] = NULL;
	return (cmd_tab);
}

void	exec(t_branch *branch, t_command_line *queue, t_info *info)
{
	char	*path;
	char	*cmd_tab;

	(void)queue;
	if (!branch->l_cmd)
		return ;
	if (branch->l_cmd)
		exec(branch->l_cmd, queue, info);
	path = check_path(info, branch->r_cmd->content);
	if (path)
	{
		cmd_tab = ready_to_exec(branch->r_cmd);
		if (!cmd_tab)
			return ;
		execve(path, cmd_tab, )
	}
}
