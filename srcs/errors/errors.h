/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:20:40 by madamou           #+#    #+#             */
/*   Updated: 2024/07/31 20:14:54 by madamou          ###   ########.fr       */
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
void	handle_unexpected_token(char *token);
void	handle_malloc_error(char *message);
void	free_and_exit(void);

#endif // !ERRORS_H
