/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_commands_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:54:16 by itahri            #+#    #+#             */
/*   Updated: 2024/09/09 04:02:02 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <termios.h>

void	free_tree(t_element *node)
{
	if (!node)
		return ;
	free_tree(node->left);
	free_tree(node->right);
	ft_free_2d(node->args);
	ft_free_2d(node->outfile);
	ft_free(node->infile_tab);
	ft_free(node);
}

void	close_file_tree(t_element *current)
{
	int	i;

	i = 0;
	if (!current)
		return ;
	if (current->type == CMD || current->type == C_BLOCK
		|| current->type == LOCAL_VAR || current->type == N_CMD)
	{
		while (current->infile && current->infile[i])
		{
			ft_close(current->infile_tab[i]);
			i++;
		}
		return ;
	}
	close_file_tree(current->left);
	close_file_tree(current->right);
}

void	execute_command_line(t_tree *tree, t_info *info)
{
	int				pid;
	int				status;
	t_tree			*tmp;
	struct termios	term;

	info->signaled = 0;
	(tcgetattr(STDOUT_FILENO, &term), set_signal_parent_exec());
	while (tree)
	{
		if ((tree->first->type == CMD && !check_built_in(tree->first->content))
			|| tree->first->type == C_BLOCK || tree->first->type == N_CMD)
		{
			pid = ft_fork(info);
			if (pid == 0)
				exec(tree->first, info, tree->first);
			close_file_tree(tree->first);
			(waitpid(pid, &status, 0), exit_status(status, info));
		}
		else
			exec(tree->first, info, tree->first);
		tmp = tree->next;
		(free_tree(tree->first), ft_free(tree));
		tree = tmp;
	}
	(tcsetattr(STDOUT_FILENO, TCSANOW, &term), check_if_signal(info));
}
