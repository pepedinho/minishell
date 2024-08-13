/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:44:20 by madamou           #+#    #+#             */
/*   Updated: 2024/08/13 21:02:18 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	outfile(t_element *node, t_info *info)
{
	int	outfile;
	int i;

	i = 0;
	outfile = -1;
	if (node->outfile)
	{
		while (node->outfile[i])
		{
			ft_close(outfile);
			if (node->file_mode[i] == R_RED)
			{
				outfile = open(node->outfile[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (outfile == -1)
					error_message(node->outfile[i]);
			}
			else if (node->file_mode[i] == RR_RED)
			{
				outfile = open(node->outfile[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (outfile == -1)
					error_message(node->outfile[i]);
			}
			i++;
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
