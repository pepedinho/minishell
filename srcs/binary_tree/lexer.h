/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:19:08 by itahri            #+#    #+#             */
/*   Updated: 2024/07/27 19:58:28 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../includes/minishell.h"

typedef struct s_branch
{
	struct s_element	*main_cmd;
	struct s_element	*r_cmd;
	struct s_element	*l_cmd;
	struct s_branch		*next;
}						t_branch;

typedef struct s_tree
{
	t_branch			*first;
}						t_tree;

// lexing
void					print_tree(t_tree *tree);

#endif
