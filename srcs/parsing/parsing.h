/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:26:17 by itahri            #+#    #+#             */
/*   Updated: 2024/07/29 10:52:43 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../includes/minishell.h"
# include "../garbage_collecting/garbage_collecting.h"

# define NO_END_QUOTE 0

/*
 * type :
 * 1 = Command
 * 2 = suffix
 * 3 = redirection
 */

typedef struct s_element
{
	int					type;
	int					relative_type;
	char				*content;
	struct s_element	*next;
	struct s_element	*before;
}						t_element;

typedef struct s_command_line
{
	t_element			*first;
	t_element			*last;
}						t_command_line;

// queue functions
t_command_line			*init_queue(void);
t_element				*add_to_queue(t_command_line *queue, char *content,
							int type);
void					free_queue(t_command_line *queue);
t_command_line			*parser(char *str);
void					print_queue(t_command_line *queue);

#endif
