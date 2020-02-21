/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:55:10 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/22 00:31:38 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		free_tab(char **arg)
{
	char 	**tab;
	int		i;

	tab = arg;
	i = -1;
	if (!tab)
		return ;
	while (arg[++i])
		ft_strdel(&arg[i]);
	free(arg);
}

void		exec_error(char *str, int c)
{
	if (c == 1)
	{
		ft_putstr(str);
		ft_putendl(": Permission denied.");
	}
	else if (c == 2)
	{
		ft_putstr(str);
		ft_putendl(": Command not found.");
	}
}

void		error_msg(char *str)
{
	ft_putstr(str);
	ft_putendl(": command not found.");
}
