/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 19:53:28 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/07 00:19:38 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

int				ft_printoperation(int r)
{
	if (r != LEFT && r != RIGHT && r != A_LEFT && r != A_DOWN &&
	r != A_UP && r != A_RIGHT && r != CTRL_W && r != HOME && r != END)
		return (1);
	return (0);
}

void			ft_cut_from_to(char **cmd, int from, int to)
{
	char		*ptr;
	char		*rest;

	ptr = ft_strsub(*cmd, 0, from);
	rest = ft_strdup(*cmd + to);
	ft_strdel(cmd);
	*cmd = ft_strjoin(ptr, rest);
	ft_strdel(&rest);
	ft_strdel(&ptr);
}

void			ft_cut(char **cmd, int r, int *i)
{
	int			from;
	int			to;

	if (r == CTRL_X)
	{
		if (g_copy.from <= g_copy.to)
		{
			from = g_copy.from;
			to = g_copy.to;
		}
		else
		{
			from = g_copy.to;
			to = g_copy.from;
		}
		*i = from;
		if (g_copy.copy != NULL)
			ft_strdel(&g_copy.copy);
		g_copy.copy = ft_strsub(*cmd, from, to);
		ft_cut_from_to(cmd, from, to);
	}
	g_copy.to = -1;
	g_copy.from = -1;
}

void			ft_copy(char *cmd, int r)
{
	int			from;
	int			to;

	if (r == CTRL_W)
	{
		if (g_copy.from < g_copy.to)
		{
			from = g_copy.from;
			to = g_copy.to;
		}
		else
		{
			to = g_copy.from;
			from = g_copy.to;
		}
		if (g_copy.copy != NULL)
			ft_strdel(&g_copy.copy);
		g_copy.copy = ft_strsub(cmd, from, to);
	}
	g_copy.to = -1;
	g_copy.from = -1;
}

void			ft_paste(char **cmd, int r, int *i)
{
	if (r == SELECT)
		g_copy.from = *i;
	if (g_copy.from != -1)
		g_copy.to = *i;
	if (r != SELECT && r != LEFT && r != RIGHT && r != A_LEFT && r != A_DOWN &&
	r != A_UP && r != A_RIGHT && r != CTRL_W && r != CTRL_X && r != CTRL_E && r
	!= HOME && r != END)
	{
		g_copy.from = -1;
		g_copy.to = -1;
	}
	if (r == CTRL_W && g_copy.from != -1 && g_copy.to != -1)
		ft_copy(*cmd, r);
	if (r == CTRL_X && g_copy.from != -1 && g_copy.to != -1)
		ft_cut(cmd, r, i);
	if (r == CTRL_E && g_copy.copy)
		ft_charjoin(cmd, g_copy.copy, i);
}
