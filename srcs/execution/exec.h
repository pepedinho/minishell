/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@contact.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 05:48:29 by madamou           #+#    #+#             */
/*   Updated: 2024/08/02 17:54:22 by itahri           ###   ########.fr       */
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

#endif // !EXEC_H
