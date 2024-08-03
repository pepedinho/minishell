/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:17:37 by madamou           #+#    #+#             */
/*   Updated: 2024/08/02 17:59:24 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# ifdef MINISHELL_H
#  undef MINISHELL_H
# endif

# include "../../includes/minishell.h"

int		ft_cd(char *directory);
void	ft_echo(char *command, int flag);
void	env(void);
int		ft_export(t_info *info, char **content);
void	print_env(t_env *env, int cas);

#endif // !BUILTINS_H
