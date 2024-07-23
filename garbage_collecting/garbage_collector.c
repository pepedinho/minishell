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

void    *ft_malloc(size_t t)
{
    static int i;
    static t_garbage *garbage;
    void *ptr;

    if (!garbage)
        garbage = init_garbage();
    ptr = malloc(t);
    if (!ptr)
        return (NULL);
    push_to_garbage(garbage, ptr);
    return (ptr);
}

void    ft_free(void *ptr)
{
    static int i;
    static t_garbage *garbage;

    if (!i)
    {
        garbage = ptr;
        return ;
    }
    destroy(garbage, ptr);
}

size_t ft_strlen(char const *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int main(int argc, char const *argv[])
{
    char *test;
    int len  = ft_strlen(argv[1]);
    test = ft_malloc(sizeof(char) * len);
    if (!test)
        return (-1);
    for (int i = 0; argv[1][i]; i++)
        test[i] = argv[1][i];
    test[len] = '\0';
    printf("oui : %s\n", test);
    ft_free(test);
    return 0;
}
