/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:26:42 by itahri            #+#    #+#             */
/*   Updated: 2024/08/13 22:54:57 by madamou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pprint_header(void)
{
	int		fd;
	char	*line;

	fd = open("srcs/receive_prompt/header.txt", O_RDONLY);
	line = get_next_line(fd);
	ft_printf("                      :=:           ");
	ft_printf("                             .:.\n");
	ft_printf("                    :@@@@@:                                    :@@@@@\n");
	ft_printf("                   :=@@@@@:          \e[33m:+####");
	ft_printf("######+.\e[0m          -@@@@@:\n");
	ft_printf("                 %@@@@@@@+        ");
	ft_printf("\e[33m:##################:\e[0m       +@@@@@@@#\n");
	ft_printf("                 @@@@@@@@@@+    \e[33m:##:=######");
	ft_printf("#########=*#\e[0m     +@@@@@@@@@@\n");
	ft_printf("                  #@@-.@@@@@@* \e[33m*#+:#=-#.");
	ft_printf("########## ##-=#*\e[0m *@@@@@@:+@@#\n");
	ft_printf("                         @@@@@\e[33m=+++++++++++++++++++++++=++=\e[0m@@@@@\n");
	ft_printf("                          :%@\e[31m::::::::::::::::::::::::::::::\e[0m@%:\n");
	ft_printf("                             \e[31m::::::::::::::::::::::::::::::\e[0m\n");
	ft_printf("                      \e[33m::::::::::::::::::::::::::::::::::::::::::::::.\e[0m\n");
	ft_printf("                    \e[33m.:==============================================:.\e[0m\n");
	while (line)
	{
		printf("%s", line);
		ft_free(line);
		line = get_next_line(fd);
	}
	ft_close(fd);
}
