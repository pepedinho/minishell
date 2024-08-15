/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:05:08 by itahri            #+#    #+#             */
/*   Updated: 2024/08/15 03:39:36 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../srcs/binary_tree/lexer.h"
# include "../srcs/builtins/builtins.h"
# include "../srcs/environement/env.h"
# include "../srcs/errors/errors.h"
# include "../srcs/execution/exec.h"
# include "../srcs/garbage_collecting/garbage_collecting.h"
# include "../srcs/parsing/parsing.h"
# include "../srcs/receive_prompt/prompt.h"
# include "../srcs/signal/signal.h"
# include "../srcs/utils/utils.h"
# include "../srcs/wildcards/wildcards.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define CMD 1
# define SFX 2
# define PIPE 31
# define R_RED 32
# define L_RED 33
# define AND 34
# define OR 35
# define LIST 36
# define RR_RED 37
# define LL_RED 38
# define FILE 4
# define H_FILE 41
# define U_TOKEN 5
# define HU_TOKEN 51
# define C_BLOCK 6
# define LOCAL_VAR 7

# define INIT 0
# define GET 1
# define PRINT 2

// PIPE
# define READ 0
# define WRITE 1

# define ERR_MALLOC 105

extern volatile sig_atomic_t	g_sigint_received;

t_tree							*smart_agencement(t_command_line *queue);

#endif
