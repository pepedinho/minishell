/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:06:33 by marvin            #+#    #+#             */
/*   Updated: 2024/08/15 10:04:19 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char				*dest;
	long unsigned int	i;

	i = -1;
	dest = ft_malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (dest == NULL)
		handle_malloc_error("strdup");
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/*int main(void)
{
	printf("%s\n", ft_strdup("je suis entrain de test!"));
}*/
