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

void	read_pipe_debug(int fd)
{
	char	buff[100];
	int		nb_read;

	nb_read = -1;
	ft_printf("debug pipe content : \n");
	while (nb_read != 0)
	{
		nb_read = read(fd, buff, 100);
		if (nb_read == -1)
			return ;
		ft_printf("%s", buff);
	}
}

void	exec(t_branch *branch, t_command_line *queue, t_info *info, int flag)
{
	char	*path;
	char	**cmd_tab;
	pid_t	pid;

	printf("non\n");
	if (!branch)
		return ;
	if (branch->l_cmd)
		exec(branch->l_cmd, queue, info, 0);
	else if (!branch->l_cmd && flag == 0)
		exec(branch, queue, info, 1);
	if (!branch->l_cmd && flag == 1)
		path = check_path(info, branch->first_cmd->content);
	else
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
				if (!cmd_tab)
					exit(EXIT_FAILURE);
				printf("debug1 : %s\n", path);
				// dup2(branch->first_cmd->fd[READ], STDIN_FILENO);
				dup2(branch->r_cmd->fd[WRITE], STDOUT_FILENO);
				// read_pipe_debug(branch->r_cmd->fd[WRITE]);
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
				printf("debug2 : %s\n", path);
				// read_pipe_debug(branch->l_cmd->r_cmd->fd[READ]);
				if (!branch->l_cmd && branch->before)
				{
					dup2(branch->r_cmd->fd[READ], STDIN_FILENO);
					dup2(branch->before->r_cmd->fd[WRITE], STDOUT_FILENO);
				}
				else if (branch->before)
				{
					dup2(branch->r_cmd->fd[READ], STDIN_FILENO);
					dup2(branch->before->r_cmd->fd[WRITE], STDOUT_FILENO);
				}
				else
				{
					dup2(branch->r_cmd->fd[READ], STDIN_FILENO);
				}
				close_fd(queue);
				if (!execve(path, cmd_tab, info->env->envp))
					printf("error execve\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	if (!branch->l_cmd && flag == 1)
	{
		close(branch->first_cmd->fd[READ]);
		close(branch->first_cmd->fd[WRITE]);
		//	close(branch->first_cmd->fd[READ]);
	}
	else
	{
		if (!branch->l_cmd && branch->before)
		{
			close(branch->r_cmd->fd[READ]);
		}
		else if (branch->before)
		{
			close(branch->r_cmd->fd[READ]);
		}
		else
			close_fd(queue);
	}
	wait(NULL);
}
