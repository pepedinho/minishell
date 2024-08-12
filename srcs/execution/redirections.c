/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:44:20 by madamou           #+#    #+#             */
/*   Updated: 2024/08/11 21:31:07 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	outfile(t_element *node, t_info *info)
{
	int	outfile;

	outfile = -1;
	if (node->outfile)
	{
		if (node->file_mode == R_RED)
		{
			outfile = open(node->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (outfile == -1)
				error_message(node->outfile);
		}
		else if (node->file_mode == RR_RED)
		{
			outfile = open(node->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (outfile == -1)
				error_message(node->outfile);
		}
	}
	if (outfile != -1)
	{
		if (dup2(outfile, STDOUT_FILENO) == -1)
			ft_fprintf(2, "%s: Error when trying to dup2\n", info->name);
		ft_close(outfile);
	}
}

void	infile(t_element *node, t_info *info)
{
	if (node->infile != -1)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			ft_fprintf(2, "%s: Error when trying to dup2\n", info->name);
		ft_close(node->infile);
	}
}
