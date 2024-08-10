/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:02:19 by madamou           #+#    #+#             */
/*   Updated: 2024/08/10 17:48:52 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# include "../../includes/minishell.h"

typedef struct s_info
{
	char			*name;
	struct s_env	*env;
	int signal_code;
}					t_info;

// Prompt
void				receive_prompt(t_info *info);
void	receive_prompt_subminishell(char *command_line,
									t_info *info);
t_info				*info_in_static(t_info *info, int cas);
char	*ft_readline(t_info *info);


#endif
