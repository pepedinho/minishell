/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:05:08 by itahri            #+#    #+#             */
/*   Updated: 2024/07/26 15:23:37 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../srcs/garbage_collecting/garbage_collecting.h"
# include "../srcs/parsing/parsing.h"
# include "../libft/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <stdbool.h>
#include <signal.h>

// Prompt
void receive_prompt(t_command_line *queue);

// Signals
void sigaction_sigint(void);
void handle_sigint(int num);

#endif
