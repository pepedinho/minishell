/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:26:17 by itahri            #+#    #+#             */
/*   Updated: 2024/07/24 18:35:47 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../garbage_collecting/garbage_collecting.h"

/*
 * type :
 * 1 = Command
 * 2 = suffix
 * 3 = redirection
 */

typedef struct s_element
{
	int					type;
	char				*content;
	struct s_element	*next;
}						t_element;

typedef struct s_command_line
{
	t_element			*first;
}						t_command_line;

#endif
