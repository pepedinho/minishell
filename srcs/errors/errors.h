/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:20:40 by madamou           #+#    #+#             */
/*   Updated: 2024/08/28 23:19:21 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# ifdef MINISHELL_H
#  undef MINISHELL_H
# endif

# include "../../includes/minishell.h"

void	error_message(char *content);
void	close_fd(t_command_line *queue);
void	handle_unexpected_token(char *token, int cas);
void	handle_malloc_error(char *message);
void	free_and_exit(int status_code);
void	message_pipe(char *limiter, int cpt);

#endif // !ERRORS_H
