/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autoco_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:10:35 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/07 00:19:05 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

char					*ft_clean_path(char *str)
{
	int					i;
	int					j;

	j = ft_strlen(str);
	i = ft_strlen(str);
	if (!(ft_strrchr(str, '/')))
		return (ft_strnew(0));
	while (str[j] != ' ' && j > 0)
		j--;
	if (str[j] == ' ')
		j++;
	while (i > 0 && str[i] != '/')
		i--;
	i++;
	return (ft_strsub(str, j, i - j));
}

t_auto					*ft_search_in_dir(char *str, t_auto *head)
{
	char				*path;
	char				*s;
	DIR					*dr;
	struct dirent		*dir;
	t_auto				*comp;

	if (!(s = ft_strrchr(str, '/')))
		path = ft_strdup(".");
	else
		path = ft_clean_path(str);
	(path[0] == '.' && path[1] == '\0') ? (s = ft_strrchr(str, ' ')) : 0;
	ft_alloc(&comp);
	head = comp;
	if (!(dr = opendir(path)) && !ft_strdel(&path))
		return (NULL);
	while ((dir = readdir(dr)) != NULL)
		if (((ft_strncmp(s, dir->d_name, ft_strlen(s)) == 0) || !s))
		{
			comp->data = ft_strdup(dir->d_name);
			ft_alloc(&comp->next);
			comp = comp->next;
		}
	closedir(dr);
	ft_strdel(&path);
	return (head);
}

t_auto					*ft_searchinpath(char *str, char **envpath)
{
	DIR					*dr;
	struct dirent		*dir;
	int					i_l[2];
	t_auto				*comp;
	t_auto				*head;

	i_l[1] = ft_strlen(str);
	ft_alloc(&comp);
	head = comp;
	i_l[0] = -1;
	while (envpath[++i_l[0]])
	{
		if (!(dr = opendir(envpath[i_l[0]])))
			return (NULL);
		while ((dir = readdir(dr)) != NULL)
			if ((ft_strncmp(str, dir->d_name, i_l[1]) == 0 || str[0] == '\0'))
			{
				comp->data = ft_strdup(dir->d_name);
				ft_alloc(&comp->next);
				comp = comp->next;
			}
		closedir(dr);
	}
	return (head);
}
