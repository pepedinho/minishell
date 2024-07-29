/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collecting.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:07:27 by itahri            #+#    #+#             */
/*   Updated: 2024/07/29 02:36:31 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTING_H
# define GARBAGE_COLLECTING_H

# include "../../includes/minishell.h"
# include <stdio.h>
# include <stdlib.h>

# define DESTROY ((void *)-1)

typedef struct s_to_destroy
{
	void				*to_destroy;
	struct s_to_destroy	*next;
}						t_to_destroy;

typedef struct s_garbage
{
	t_to_destroy		*first;
	int					total_alloc;
	int					total_free;
}						t_garbage;

// garbage queue functions
t_to_destroy			*push_to_garbage(t_garbage *garbage, void *ptr);
t_garbage				*init_garbage(void);
void					destroy(t_garbage *garbage, t_to_destroy *elem);
void					destroy_all(t_garbage *garbage);

// garbage collector functions
void					*ft_malloc(long int t);
void					ft_free(void *ptr);
void					free_and_exit(char *error, char *with);

/*
 * HOW TO USE
 * alloc your ptr with ft_malloc :
 *    ptr = ft_malloc(size);
 * free with ft_free() :
 *    ft_free(ptr);
 * before exit minishell free all garbage_collector with :
 *    ft_free(DESTROY);
 */

#endif
