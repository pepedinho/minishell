/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:17:37 by madamou           #+#    #+#             */
/*   Updated: 2024/08/04 21:55:26 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# ifdef MINISHELL_H
#  undef MINISHELL_H
# endif

# include "../../includes/minishell.h"

int		ft_cd(char *directory);
void	ft_echo(char **args, t_info *info);
int		ft_export(t_info *info, char **content);
void	print_env(t_env *env, int cas, t_info *info);
char	*ft_pwd(int cas, t_info *info);
void	ft_exit(char **args);

#endif // !BUILTINS_H
