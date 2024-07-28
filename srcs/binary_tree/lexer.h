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
	struct s_element	*main_cmd;
	struct s_element	*r_cmd;
	t_sfx				*r_cmd_sfx;
	struct s_element	*l_cmd;
	t_sfx				*l_cmd_sfx;
	struct s_branch		*next;
}						t_branch;

typedef struct s_tree
{
	t_branch			*first;
}						t_tree;

// lexing
void					print_tree(t_tree *tree);

#endif