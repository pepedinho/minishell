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
	if (cnt - 1 < 0)
		cnt = 0;
	else
		cnt--;
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
		printf("[3]/!\\ DEBUG  /!\\ : [%d]%s\n", elem->d_type, elem->d_name);
		if (elem->d_name[0] != '.' && ft_strstr(elem->d_name, patern))
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

char	*get_new_path(char *path, int depth, char *dirname)
{
	char	*result;
	char	*first_elem;
	int		dpth;
	int		i;

	dpth = 0;
	i = 0;
	while (path[i])
	{
		if (path[i] == '/' && dpth == depth - 1)
			break ;
		if (path[i] == '/')
			dpth++;
		i++;
	}
	printf("[[1][DEBUG]] path : %s\n", path);
	first_elem = ft_substr(path, 0, i);
	if (first_elem[ft_strlen(first_elem) - 1] != '/')
		result = ft_sprintf("%s/%s", first_elem, dirname);
	else
		result = ft_strjoin(first_elem, dirname);
	printf("[[2][DEBUG]] result : %s\n", result);
	return (result);
}

int	compare(char *path, char *dirname)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (path[i] && path[i] != '/')
		i++;
	while (dirname[j] && dirname[j] != '/')
		j++;
	if (j != i)
		return (0);
	return (1);
}

// TODO: add protection for to deep path exemple :
// srcs/*/*/*.c this path is too deep so we have to return "srcs/*/*/*.c" litteraly
// without modification
void	rec_open(char **tab, int depth, int cnt, t_command_line *queue)
{
	int				tot_cnt;
	DIR				*dir;
	char			*new_dir;
	struct dirent	*elem;

	tot_cnt = cnt_file(tab[DIRNAME]);
	// if (!depth)
	//	return ;
	// printf("[1]/!\\debug/!\\ : %s\n", tab[DIRNAME]);
	dir = opendir(tab[DIRNAME]);
	if (!dir)
		return ;
	elem = readdir(dir);
	while (elem)
	{
		if (elem->d_type == 4 && !ft_strstr(elem->d_name, ".") && depth > 0
			&& cnt == tot_cnt)
		{
			// printf("debug[1] : %s\n", ft_strstr(elem->d_name, "."));
			// new_dir = ft_strjoin(tab[DIRNAME], elem->d_name);
			if (!compare(tab[DIRNAME], elem->d_name))
			{
				printf("list : %s/\n\tdepth : %d\n", tab[DIRNAME], depth);
				new_dir = get_new_path(tab[DIRNAME], depth, elem->d_name);
				list_file(new_dir, tab[PATERN], queue);
				tab[DIRNAME] = new_dir;
				// printf("debug[2] : %s\n", elem->d_name);
				rec_open(tab, depth - 1, 0, queue);
			}
		}
		else if (elem->d_type == 4 && !ft_strstr(elem->d_name, ".")
			&& depth > 0)
		{
			// list_file(tab[DIRNAME], tab[PATERN], queue);
			// printf("debug[1] : %s\n", ft_strstr(elem->d_name, "."));
			// new_dir = ft_strjoin(tab[DIRNAME], elem->d_name);
			if (!compare(tab[DIRNAME], elem->d_name))
			{
				printf("debug : %s\n\tdepth : %d\n", tab[DIRNAME], depth);
				new_dir = get_new_path(tab[DIRNAME], depth, elem->d_name);
				tab[DIRNAME] = new_dir;
				rec_open(tab, depth - 1, 0, queue);
			}
			// printf("debug[2] : %s\n", elem->d_name);
		}
		else if (elem->d_type == 4 && !ft_strstr(elem->d_name, "."))
		{
			printf(" simple list : %s/%s\n\tdepth : %d\n", tab[DIRNAME],
				elem->d_name, depth);
			list_file(tab[DIRNAME], tab[PATERN], queue);
			return ;
		}
		else if (elem->d_type != 4 && depth == 0 && elem->d_name[0] != '.'
			&& cnt == tot_cnt)
		{
			printf("new list : %s/%s\n\tdepth : %d\n", tab[DIRNAME],
				elem->d_name, depth);
			list_file(tab[DIRNAME], tab[PATERN], queue);
		}
		else
			printf(" lost : %s/%s\n\tdepth : %d | cnt : %d/%d\n", tab[DIRNAME],
				elem->d_name, depth, cnt, tot_cnt);
		elem = readdir(dir);
		cnt++;
	}
	// printf("[2]/!\\debug/!\\ : %s\n", tab[DIRNAME]);
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

int	rec_depth_check(char **tab, int depth, int cnt)
{
	DIR				*dir;
	struct dirent	*elem;
	char			*new_dir;

	if (cnt >= depth)
		return (cnt);
	dir = opendir(tab[DIRNAME]);
	if (!dir)
		return (0);
	elem = readdir(dir);
	while (elem)
	{
		if (elem->d_name[0] != '.' && elem->d_type == 4)
		{
			new_dir = get_new_path(tab[DIRNAME], 0, elem->d_name);
			tab[DIRNAME] = new_dir;
			return (rec_depth_check(tab, depth - 1, cnt + 1));
		}
		elem = readdir(dir);
	}
	return (cnt);
}

int	check_depth(char **tab, int depth, int cnt)
{
	DIR				*dir;
	struct dirent	*elem;
	char			*new_dir;
	int				current_depth;
	int				last_max_depth;

	if (cnt >= depth)
		return (cnt);
	dir = opendir(tab[DIRNAME]);
	if (!dir)
		return (0);
	last_max_depth = 0;
	elem = readdir(dir);
	while (elem)
	{
		if (elem->d_name[0] && elem->d_type == 4)
		{
			new_dir = get_new_path(tab[DIRNAME], 0, elem->d_name);
			tab[DIRNAME] = new_dir;
			current_depth = rec_depth_check(tab, depth, 0);
			printf("debug : cur_depth : %d cur_file : %s\n", current_depth,
				new_dir);
			if (last_max_depth < current_depth)
				last_max_depth = current_depth;
		}
		elem = readdir(dir);
	}
	return (last_max_depth + 1);
}

int	expend_wcards(char *path, t_command_line *queue)
{
	char	**tab;
	int		max_depth;

	tab = get_path_and_format(path);
	max_depth = check_depth(tab, get_depth(path), 0);
	tab = get_path_and_format(path);
	printf("\nmax depth found : %d depth : %d\n\n", max_depth, get_depth(path));
	rec_open(tab, get_depth(path) - 1, 0, queue);
	return (0);
}
