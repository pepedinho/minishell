/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@contact.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 15:01:48 by itahri            #+#    #+#             */
/*   Updated: 2024/07/23 15:51:42 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collecting.h"

void	ft_free(void *ptr);

void	*ft_malloc(size_t t)
{
	static int			i;
	static t_garbage	*garbage;
	void				*ptr;

	if (!garbage)
		garbage = init_garbage();
	ptr = malloc(t);
	if (!ptr)
		return (NULL);
	push_to_garbage(garbage, ptr);
	if (!i)
		ft_free(garbage);
	i++;
	return (ptr);
}

void	ft_free(void *ptr)
{
	static int			i = -1;
	static t_garbage	*garbage;

	if (ptr == DESTROY)
	{
		destroy_all(garbage);
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

size_t	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	main(int argc, char const *argv[])
{
	char	*test;
	char	*test2;
	int		len;
	int		len2;

	len = ft_strlen(argv[1]);
	len2 = ft_strlen(argv[2]);
	test = ft_malloc(sizeof(char) * len);
	test2 = ft_malloc(sizeof(char) * len);
	if (!test)
		return (-1);
	for (int i = 0; argv[1][i]; i++)
		test[i] = argv[1][i];
	test[len - 1] = '\0';
	printf("oui : %s\n", test);
	for (int i = 0; argv[1][i]; i++)
		test2[i] = argv[2][i];
	test2[len2 - 1] = '\0';
	printf("oui : %s\n", test2);
	ft_free(test2);
	ft_free(test);
	ft_free(DESTROY);
	return (0);
}
