/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:02:19 by madamou           #+#    #+#             */
/*   Updated: 2024/08/04 16:51:06 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "../../includes/minishell.h"

typedef struct s_info
{
	char			*name;
	struct s_env	*env;
}					t_info;

// Prompt
void				receive_prompt(t_info *info);
void	receive_prompt_subminishell(char *command_line,
									t_info *info);
t_info				*info_in_static(t_info *info, int cas);

#endif
