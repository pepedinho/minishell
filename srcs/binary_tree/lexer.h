/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:19:08 by itahri            #+#    #+#             */
/*   Updated: 2024/07/28 19:30:02 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../includes/minishell.h"

typedef struct s_cmd_sfx
{
	struct s_element	*suffix;
	struct s_cmd_sfx	*next;
}						t_cmd_sfx;

typedef struct s_sfx
{
	t_cmd_sfx			*first;
}						t_sfx;

typedef struct s_branch
{
	struct s_element	*redirect;
	struct s_element	*r_cmd;
	struct s_sfx		*r_sfx;
	struct s_branch		*l_cmd;
	struct s_element	*first_cmd;
}						t_branch;

typedef struct s_tree
{
	t_branch			*first;
}						t_tree;

// lexing
void					print_tree(t_tree *tree);
int						is_a_redirect(int type);

#endif
