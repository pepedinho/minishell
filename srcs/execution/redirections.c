/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 14:44:20 by madamou           #+#    #+#             */
/*   Updated: 2024/08/26 23:27:21 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

int	ft_open_infile(char *file, int flag)
{
	int	fd;

	fd = open(file, flag);
	if (fd == -1)
		(error_message(file), free_and_exit(1));
	return (fd);
}

int	ft_open_outfile(char *file, int flag)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | flag, 0644);
	if (fd == -1)
		(error_message(file), free_and_exit(1));
	return (fd);
}

int	outfile(t_element *node, t_info *info)
{
	int	outfile;
	int	i;

	i = 0;
	outfile = -1;
	while (node->outfile && node->outfile[i])
	{
		if (node->file_mode[i] == R_RED)
			outfile = ft_open_outfile(node->outfile[i], O_TRUNC);
		else if (node->file_mode[i] == RR_RED)
			outfile = ft_open_outfile(node->outfile[i], O_APPEND);
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
			node->infile_tab[i] = ft_open_infile(node->infile[i], O_RDONLY);
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
