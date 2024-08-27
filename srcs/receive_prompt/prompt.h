/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:02:19 by madamou           #+#    #+#             */
/*   Updated: 2024/08/27 16:09:08 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "../../includes/minishell.h"
# include "../parsing/parsing.h"

# define CLR "\001\033[0;34m\002"
# define ND "[0;31m$\001\033[0m\002"

// Header
void			pprint_header(void);

// Prompt
void			receive_prompt(t_info *info);
void			receive_prompt_subminishell(char *command_line, t_info *info);
t_info			*info_in_static(t_info *info, int cas);
char			*ft_readline(t_info *info);
char			**prepare_args_to_exec(t_element *cmd);
void			stock_infile_outfile(t_change *change, t_element **node);

// utils1
void			queue_add_back(t_command_line **queue, t_command_line *new);
t_command_line	*change_queue(t_command_line *queue);

// utils2
void			tree_add_back(t_tree **tree, t_tree *new);
char			*get_prompt(t_info *info);
t_command_line	*parsing(char *command_line, t_info *info);

#endif
