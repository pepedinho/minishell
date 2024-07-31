/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:01:48 by itahri            #+#    #+#             */
/*   Updated: 2024/07/31 20:20:22 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collecting.h"

void	*ft_malloc(long int t)
{
	static int			i;
	static t_garbage	*garbage;
	void				*ptr;

	if (!garbage)
		garbage = init_garbage();
	if (t == -1)
	{
		garbage = NULL;
		return (NULL);
	}
	ptr = malloc(t);
	if (!ptr)
		return (NULL);
	push_to_garbage(garbage, ptr);
	if (!garbage->total_alloc)
		ft_free(garbage);
	i++;
	garbage->total_alloc++;
	return (ptr);
}

void	ft_free(void *ptr)
{
	static int			i;
	static t_garbage	*garbage;

	i = -1;
	if (ptr == DESTROY)
	{
		i = -1;
		destroy_all(garbage);
		garbage = ft_malloc(-1);
		return ;
	}
	if (!ptr)
		return ;
	if (i == -1)
	{
		garbage = ptr;
		i++;
		return ;
	}
	destroy(garbage, ptr);
}
