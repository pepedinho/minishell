/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:12:42 by madamou           #+#    #+#             */
/*   Updated: 2024/07/31 18:52:10 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../../includes/minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	char			**split;
	struct s_env	*next;
}					t_env;

t_env				*env_in_struct(char **envp);
void				free_env(t_env *env);

#endif // !ENV_H
