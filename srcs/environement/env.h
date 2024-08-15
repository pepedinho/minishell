/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:12:42 by madamou           #+#    #+#             */
/*   Updated: 2024/08/15 19:54:02 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../../includes/minishell.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	char			**envp;
	int				global;
	struct s_env	*next;
}					t_env;

# define GLOBAL 1
# define LOCAL 0
# define ALL 2

t_env				*env_in_struct(char **envp);
void				free_env(t_env *env);
char				**t_env_to_envp(t_env *env, int cas);
t_env *search_in_env(char *key);
t_env				*init_env(char *envp, int cas);
void				add_back_env(t_env **env, t_env *new);
int is_a_good_variable(char *str);

#endif // !ENV_H
