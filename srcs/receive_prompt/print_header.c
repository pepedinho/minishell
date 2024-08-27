/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madamou <madamou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 23:26:42 by itahri            #+#    #+#             */
/*   Updated: 2024/08/27 16:21:47 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	first_part_header(void)
{
	ft_printf("                      :=:           ");
	ft_printf("                             .:.\n");
	ft_printf("                    :@@@@@:               ");
	ft_printf("                     :@@@@@\n");
	ft_printf("                   :=@@@@@:          \e[33m:+####");
	ft_printf("######+.\e[0m          -@@@@@:\n");
	ft_printf("                 %@@@@@@@+        ");
	ft_printf("\e[33m:##################:\e[0m       +@@@@@@@#\n");
	ft_printf("                 @@@@@@@@@@+    \e[33m:##:=######");
	ft_printf("#########=*#\e[0m     +@@@@@@@@@@\n");
	ft_printf("                  #@@-.@@@@@@* \e[33m*#+:#=-#.");
	ft_printf("########## ##-=#*\e[0m *@@@@@@:+@@#\n");
	ft_printf("                         @@@@@\e[33m=++++++");
	ft_printf("+++++++++++++++++=++=\e[0m@@@@@\n");
	ft_printf("                          :%@\e[31m::::::::");
	ft_printf("::::::::::::::::::::::\e[0m@%:\n");
	ft_printf("                             \e[31m::::::::");
	ft_printf("::::::::::::::::::::::\e[0m\n");
	ft_printf("                      \e[33m:::::::::::::::");
	ft_printf(":::::::::::::::::::::::::::::::.\e[0m\n");
	ft_printf("                    \e[33m.:===============");
	ft_printf("===============================:.\e[0m\n");
}

void	pprint_header(void)
{
	int		fd;
	char	*line;

	fd = open("srcs/receive_prompt/header.txt", O_RDONLY);
	first_part_header();
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		ft_free(line);
		line = get_next_line(fd);
	}
	ft_close(fd);
}
