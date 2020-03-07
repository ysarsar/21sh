/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 06:04:47 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/04 02:21:56 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char		*free_tabs(char **arg)
{
	char	**tabs;
	int		i;

	tabs = arg;
	i = -1;
	if (!tabs)
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

int			free_tabs2(char **args, char **arr)
{
	if (args)
		free_tabs(args);
	if (arr)
		free_tabs(arr);
	return (1);
}

int			is_special(char c)
{
	if (c == '#' || c == '/' || c == '~' || c == '@'
		|| c == '^' || c == '$')
		return (1);
	return (0);
}
