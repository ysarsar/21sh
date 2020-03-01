/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 06:04:47 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/01 14:43:40 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char		*free_tab(char **arg)
{
	char	**tab;
	int		i;

	tab = arg;
	i = -1;
	if (!tab)
		return (NULL);
	while (arg[++i])
		ft_strdel(&arg[i]);
	free(arg);
	return (NULL);
}

void		free_str(char *ptr, char *tmp)
{
	ft_strdel(&ptr);
	ft_strdel(&tmp);
}

char		*ft_changedir(char *str, char *cwd)
{
	char	*var;
	char	*path;

	var = ft_strjoin(cwd, "/");
	path = ft_strjoin(var, str);
	ft_strdel(&var);
	return (path);
}

int			free_tab2(char **args, char **arr)
{
	if (args)
		free_tab(args);
	if (arr)
		free_tab(arr);
	return (1);
}
