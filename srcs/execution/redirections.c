/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:44:20 by madamou           #+#    #+#             */
/*   Updated: 2024/08/25 16:07:06 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

int	outfile(t_element *node, t_info *info)
{
	int	outfile;
	int	i;

	i = 0;
	outfile = -1;
	while (node->outfile && node->outfile[i])
	{
		if (node->file_mode[i] == R_RED)
		{
			outfile = open(node->outfile[i], O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (outfile == -1)
				(error_message(node->outfile[i]), free_and_exit(1));
		}
		else if (node->file_mode[i] == RR_RED)
		{
			outfile = open(node->outfile[i], O_WRONLY | O_CREAT | O_APPEND,
					0644);
			if (outfile == -1)
				(error_message(node->outfile[i]), free_and_exit(1));
		}
		if (dup2(outfile, STDOUT_FILENO) == -1)
		{
			ft_fprintf(2, "%s: Error when trying to dup2\n", info->name);
			(ft_close(outfile), free_and_exit(-1));
		}
		ft_close(outfile);
		i++;
	}
	return (1);
}

int	infile(t_element *node, t_info *info, t_element *first)
{
	int	i;

	i = 0;
	while (node->infile && node->infile[i])
	{
		if (node->infile_tab[i] == -1)
		{
			node->infile_tab[i] = open(node->infile[i], O_RDONLY);
			if (node->infile_tab[i] == -1)
				(error_message(node->infile[i]), free_and_exit(1));
		}
		if (dup2(node->infile_tab[i], STDIN_FILENO) == -1)
		{
			ft_fprintf(2, "%s: Error when trying to dup2\n", info->name);
			(close_file_tree(first), free_and_exit(-1));
		}
		i++;
	}
	close_file_tree(first);
	return (1);
}
