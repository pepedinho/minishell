/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 05:48:29 by madamou           #+#    #+#             */
/*   Updated: 2024/08/18 02:35:10 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# ifdef MINISHELL_H
#  undef MINISHELL_H
# endif

# define BUILT_IN ((void *)-1)

# include "../../includes/minishell.h"

// Before exec
int		global_check(struct s_command_line *queue, t_info *info);

// Path
char	*find_path(char *command, t_info *info);

// Exec
void	execute_command_line(t_tree *tree);
void	exec(t_element *node, t_info *info, t_element *first);

// Heredoc
void	here_doc(t_element *tmp);
char	*ft_parse_line(char *line);
char	*ft_is_evn_variable(char *line, char **envp);

// Utils
int		check_if_fork(t_element *node);
int		ft_fork(void);
char	**ready_to_exec(t_element *cmd);
void	exit_status(int status, t_info *info);
void ft_close(int fd);
void close_file_tree(t_element *current);

// Redirection
int	infile(t_element *node, t_info *info, t_element *first);
int	outfile(t_element *node, t_info *info);

// Builtins
int		check_built_in(char *command);
void	only_builtin(t_element *node, t_info *info, t_element *first);
void	exec_built_in(t_element *node, t_info *info);

// Operators
void or (t_element * node, t_info *info, t_element *first);
void and (t_element * node, t_info *info, t_element *first);
void	ft_pipe(t_element *node, t_info *info, t_element *first);

#endif // !EXEC_H
