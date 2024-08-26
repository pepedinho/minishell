/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:19:08 by itahri            #+#    #+#             */
/*   Updated: 2024/08/26 22:50:41 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../../includes/minishell.h"

typedef struct s_tree
{
	struct s_element	*first;
	struct s_tree		*next;
}						t_tree;

int						is_a_operator(int type);
// AST utils
int	check_type(t_element *first, t_element *current);
void	first_join(t_tree *tree, t_element *first);
void	first_join_right(t_tree *tree, t_element *first);
t_tree	*replace_submit_right(t_tree *tree, t_element *current);
t_tree	*fill_right(t_tree *tree, t_element **current);

#endif
