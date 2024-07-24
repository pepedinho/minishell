/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collecting.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@contact.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:07:27 by itahri            #+#    #+#             */
/*   Updated: 2024/07/23 15:35:56 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GARBAGE_COLLECTING_H
# define GARBAGE_COLLECTING_H
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
void					*ft_malloc(size_t t);
void					ft_free(void *ptr);

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