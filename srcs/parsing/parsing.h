/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 18:26:17 by itahri            #+#    #+#             */
/*   Updated: 2024/08/28 00:08:00 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../../includes/minishell.h"
# include "../garbage_collecting/garbage_collecting.h"

# define NO_END_QUOTE 0
# define S_U_EOF "minishell: unexpected EOF while looking for matching `''"
# define D_U_EOF "minishell: unexpected EOF while looking for matching `\"'"

/*
 * type :
 * 1 = Command
 * 2 = suffix
 * 3 = redirection
 * 4 = file (go to minishell.h to see more)
 */

/*
 * path      = path to the  command to execute
 * fd        = tab of 2 fd for pipe communication betwen process
 * in_output = input or output_file
 */
typedef struct s_element
{
	int						type;
	char					*content;
	int						fd;
	char					**infile;
	int						*infile_tab;
	struct s_element		*left;
	struct s_element		*right;
	char					**args;
	char					**outfile;
	int						*file_mode;
	struct s_element		*next;
	struct s_element		*before;
}							t_element;

typedef struct s_change
{
	int						*file_mode;
	char					**output;
	char					**infile;
	int						*infile_tab;
}							t_change;

typedef struct s_info
{
	char					*name;
	struct s_env			*env;
	int						signal_code;
}							t_info;

typedef struct s_tree
{
	struct s_element		*first;
	struct s_tree			*next;
}							t_tree;

/*
 * heredoc_flag = 1 if there is some in heredoc in command
 *                |
 *                --> 0 if ther is no heredoc in command
 */

typedef struct s_command_line
{
	int						heredoc_flag;
	int						u_token_flag;
	int						u_heredoc_token_flag;
	int						open_quotes_flag;
	int						open_parenthesis_flag;
	t_element				*first;
	t_element				*last;
	struct s_command_line	*next;
}							t_command_line;

// queue functions
t_command_line				*init_queue(void);
t_element					*add_to_queue(t_command_line *queue, char *content,
								int type);
void						free_queue(t_command_line *queue);
t_command_line				*parser(char *str, t_info *info);
void						print_queue(t_command_line *queue);
void						free_node_queue(t_element *node);
void						check_if_command_before(t_element *tmp,
								t_element *new);
t_element					*create_new_element(int type, char *content);

// utils
int							is_a_separator(char c);
int							assigne_type(char *redirection,
								t_command_line *queue);
int							is_a_quotes(char c);
char						*expand_if_necessary(char *str);
int							is_redirection(t_element *elem);
int							is_space(char c);
int							check_for_wcards(t_command_line *queue, char *str);

// Parser uitls 2
void						continue_until_find(int *i, int *j, char *str,
								char to_find);
int							add_prth_ext(t_command_line *queue, char *str,
								int *i, int j);
int							add_redirect(t_command_line *queue, char *str,
								int *i);
int							add_command(t_command_line *queue, char *str,
								int *i);

// Before parsing
char						*check_if_command_line_is_good(char *str,
								t_command_line *queue);

// Check queue
int							check_for_parenthesis(t_command_line *queue,
								t_info *info);
int							check_first_and_last_node_queue(t_command_line *q);

// Expand
char						*if_normal(char *str, int *i);
char						*if_dollar(char *str, int *i);
char						*normal_or_dollar(char *str, int *i, int j);
char						*if_dquote(char *str, int *i);
char						*if_cursh(char *str, int *i);
char						*if_quote(char *str, int *i);

#endif
