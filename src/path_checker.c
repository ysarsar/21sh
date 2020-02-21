/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 23:35:51 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/22 00:15:32 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	char	*find_path(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], "PATH=", 5) == 0)
			return (tab[i]);
		i++;
	}
	return (NULL);
}

char			*valid_path(char *cmd_name, char **tab)
{
	char	*p;
	char	*str1;
	char	*str2;
	char	**path;
	int		i;

	i = -1;
	if (!tab)
		return (NULL);
	if (!(p = find_path(tab)))
		return (NULL);
	path = ft_strsplit(&p[5], ':');
	while (path[++i])
	{
		str1 = ft_strjoin(path[i], "/");
		str2 = ft_strjoin(str1, cmd_name);
		ft_strdel(&str1);
		if (access(str2, F_OK) == 0)
		{
			free_tab(path);
			return (str2);
		}
		ft_strdel(&str2);
	}
	free_tab(path);
	return (NULL);
}

