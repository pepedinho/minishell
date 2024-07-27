/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:05:08 by itahri            #+#    #+#             */
/*   Updated: 2024/07/27 19:06:22 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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

// Signals
void	sigaction_sigint(void);
void	handle_sigint(int num);

#endif
