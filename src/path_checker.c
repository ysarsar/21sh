/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 23:35:51 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/27 23:16:18 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	char	*find_path(char **tabs)
{
	int i;

	i = 0;
	while (tabs[i])
	{
		if (ft_strncmp(tabs[i], "PATH=", 5) == 0)
			return (tabs[i]);
		i++;
	}
	return (NULL);
}

char			*valid_path(char *cmd_name, char **tabs)
{
	char	*p;
	char	*str1;
	char	*str2;
	char	**path;
	int		i;

	i = -1;
	if (!(p = find_path(tabs)) || !tabs)
		return (NULL);
	path = ft_strsplit(&p[5], ':');
	while (path[++i])
	{
		str1 = ft_strjoin(path[i], "/");
		str2 = ft_strjoin(str1, cmd_name);
		ft_strdel(&str1);
		if (access(str2, F_OK) == 0)
		{
			free_tabs(path);
			return (str2);
		}
		ft_strdel(&str2);
	}
	free_tabs(path);
	return (NULL);
}
