/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 05:48:29 by madamou           #+#    #+#             */
/*   Updated: 2024/08/02 19:36:11 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# ifdef MINISHELL_H
#  undef MINISHELL_H
# endif

# include "../../includes/minishell.h"

// Before exec
int		global_check(struct s_command_line *queue);

// Path
char	*find_path(char *command, t_info *info);

// Exec
void	execute_command_line(t_tree *tree);
int		ft_fork(void);
void	exec(t_element *node);
char    **ready_to_exec(t_element *cmd);

#endif // !EXEC_H
