/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:05:08 by itahri            #+#    #+#             */
/*   Updated: 2024/07/28 23:45:08 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../srcs/binary_tree/lexer.h"
# include "../srcs/garbage_collecting/garbage_collecting.h"
# include "../srcs/parsing/parsing.h"
# include "../srcs/receive_prompt/prompt.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>

# define CMD 1
# define SFX 2
# define PIPE 31
# define R_RED 32
# define L_RED 33
# define AND 34
# define FILE 4

# define ERR_MALLOC -1
# define MALLOC_MESS "Error malloc when allocate for"

extern int	g_signal_code;

// Signals
void		sigaction_sigint(void);
void		handle_sigint(int num);

t_tree		*smart_agencement(t_command_line *queue);

#endif
