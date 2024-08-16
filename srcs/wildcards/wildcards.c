/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahri <itahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 03:35:50 by itahri            #+#    #+#             */
/*   Updated: 2024/08/15 04:22:57 by itahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	cnt_file(char *dirname)
{
	DIR				*dir;
	struct dirent	*elem;
	int				cnt;

	cnt = 0;
	dir = opendir(dirname);
	if (!dir)
		return (0);
	elem = readdir(dir);
	while (elem)
	{
		cnt++;
		elem = readdir(dir);
	}
	return (cnt);
}

void	list_file(char *dirname, char *patern, t_command_line *queue)
{
	DIR				*dir;
	struct dirent	*elem;

	dir = opendir(dirname);
	if (!dir)
		return ;
	elem = readdir(dir);
	while (elem)
	{
		printf("/!\\ DEBUG /!\\ : [%d]%s\n", elem->d_type, elem->d_name);
		if (ft_strstr(elem->d_name, patern) && elem->d_name[0] != '.')
		{
			if (dirname[ft_strlen(dirname) - 1] != '/')
				add_to_queue(queue, ft_sprintf("%s/%s", dirname, elem->d_name),
					SFX);
			else
				add_to_queue(queue, ft_strjoin(dirname, elem->d_name), SFX);
		}
		elem = readdir(dir);
	}
}

char	*get_new_path(char *path, int depth)
{
	char	*result;
	int		depth_cnt;
	int		i;

	i = 0;
	while (path[i])
	{
		// TODO: add depth detection to change path corectly
		if (result[i] == '/' && depth_cnt)
			i++;
	}
}

void	rec_open(char **tab, int depth, int cnt, t_command_line *queue)
{
	int				tot_cnt;
	DIR				*dir;
	char			*new_dir;
	struct dirent	*elem;

	tot_cnt = cnt_file(tab[DIRNAME]);
	if (!depth)
		return ;
	printf("[1]/!\\debug/!\\ : %s\n", tab[DIRNAME]);
	dir = opendir(tab[DIRNAME]);
	if (!dir)
		return ;
	elem = readdir(dir);
	while (elem)
	{
		if (elem->d_type == 4 && !ft_strstr(elem->d_name, ".")
			&& cnt == tot_cnt)
		{
			// printf("debug[1] : %s\n", ft_strstr(elem->d_name, "."));
			new_dir = ft_strjoin(tab[DIRNAME], elem->d_name);
			list_file(new_dir, tab[PATERN], queue);
			tab[DIRNAME] = new_dir;
			// printf("debug[2] : %s\n", elem->d_name);
			rec_open(tab, depth - 1, 0, queue);
		}
		else if (elem->d_type == 4 && !ft_strstr(elem->d_name, "."))
		{
			list_file(tab[DIRNAME], tab[PATERN], queue);
			// printf("debug[1] : %s\n", ft_strstr(elem->d_name, "."));
			new_dir = ft_strjoin(tab[DIRNAME], elem->d_name);
			tab[DIRNAME] = new_dir;
			// printf("debug[2] : %s\n", elem->d_name);
			rec_open(tab, depth, cnt + 1, queue);
		}
		elem = readdir(dir);
	}
	printf("[2]/!\\debug/!\\ : %s\n", tab[DIRNAME]);
}

int	get_depth(char *str)
{
	int	i;
	int	depth;

	depth = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '/' && str[i + 1] == '*')
			depth++;
		i++;
	}
	return (depth);
}

char	**get_path_and_format(char *str)
{
	char	**tab;
	int		i;
	int		j;

	tab = malloc(sizeof(char *) * 3);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '/' && str[i + 1] == '*')
		{
			tab[0] = ft_substr(str, 0, i + 1);
			while (str[i] && (str[i] == '/' || str[i] == '*'))
				i++;
			j = i;
			while (str[j] && str[j] != ' ' && str[j] != '/')
				j++;
			tab[1] = ft_substr(str, i, j - 1);
			tab[2] = NULL;
			break ;
		}
		i++;
	}
	return (tab);
}

int	expend_wcards(char *path, t_command_line *queue)
{
	char	**tab;
	int		i;

	i = 0;
	tab = get_path_and_format(path);
	rec_open(tab, get_depth(path), 0, queue);
	return (0);
}
