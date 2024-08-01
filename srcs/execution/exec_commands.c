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

	i = 0;
	env = info->env;
	while (env && ft_strcmp(env->key, "PATH"))
		env = env->next;
	while (env->split_value[i])
	{
		path = ft_sprintf("%s/%s", env->split_value[i], cmd);
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
	current = cmd;
	while (current && !is_a_redirect(current->type))
	{
		i++;
		current = current->next;
	}
	current = cmd;
	cmd_tab = ft_malloc(sizeof(char *) * (i + 1));
	if (!cmd_tab)
		return (NULL);
	i = 0;
	while (current && !is_a_redirect(current->type))
	{
		cmd_tab[i] = current->content;
		current = current->next;
		i++;
	}
	cmd_tab[i] = NULL;
	return (cmd_tab);
}

void	exec(t_branch *branch, t_command_line *queue, t_info *info, int flag)
{
	char	*path;
	char	**cmd_tab;
	pid_t	pid;
	int		i;

	if (!branch)
		return ;
	if (branch->l_cmd)
		exec(branch->l_cmd, queue, info, 0);
	else if (!branch->l_cmd && flag == 0)
		exec(branch, queue, info, 1);
	path = check_path(info, branch->r_cmd->content);
	// TODO: fd not close somewhere
	if (path)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("pid\n");
			if (!branch->l_cmd && flag == 1)
			{
				cmd_tab = ready_to_exec(branch->first_cmd);
				i = -1;
				while (cmd_tab[++i])
					printf("debug[%d] : %s\n", i, cmd_tab[i]);
				if (!cmd_tab)
					return ;
				printf("debug1 : %s\n", branch->r_cmd->content);
				dup2(branch->first_cmd->fd[READ], STDIN_FILENO);
				dup2(branch->r_cmd->fd[WRITE], STDOUT_FILENO);
				(close(branch->first_cmd->fd[READ]),
					close(branch->r_cmd->fd[WRITE]));
				close_fd(queue);
				if (!execve(path, cmd_tab, info->env->envp))
					printf("error execve\n");
				exit(EXIT_FAILURE);
			}
			else
			{
				cmd_tab = ready_to_exec(branch->r_cmd);
				if (!cmd_tab)
					return ;
				printf("gg\n");
				printf("debug2 : %s\n", branch->l_cmd->r_cmd->content);
				dup2(branch->l_cmd->r_cmd->fd[READ], STDIN_FILENO);
				dup2(branch->r_cmd->fd[WRITE], STDOUT_FILENO);
				close_fd(queue);
				if (!execve(path, cmd_tab, info->env->envp))
					printf("error execve\n");
				exit(EXIT_FAILURE);
			}
		}
		close_fd(queue);
		wait(NULL);
	}
}
