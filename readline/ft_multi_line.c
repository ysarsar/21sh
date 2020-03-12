/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 20:31:06 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/07 00:20:24 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

void					ft_alt_up_multi(int *i, char *str, int r, int prp)
{
	t_xy				ij;
	int					j;

	if (r == A_UP && *i > 0)
	{
		ij = ft_get_multi(*i, prp, str);
		if (ij.y == 0)
			return ;
		if (str[*i] == '\n')
			(*i)--;
		j = ij.x;
		while (*i > 0 && str[*i] != '\n')
			(*i)--;
		(*i > 0) ? (*i)-- : 0;
		while (*i > 0 && str[*i] != '\n')
			(*i)--;
		(*i)++;
		while (str[*i] && str[*i] != '\n' && j > 0)
		{
			j--;
			(*i)++;
		}
		if (ij.y == 1 && str[*i] != '\n')
			*i = *i - prp - 1 > 0 ? *i - prp - 1 : 0;
	}
}

void					ft_alt_down_multi(int *i, char *str, int r, int prp)
{
	t_xy				ij;
	int					j;

	if (r == A_DOWN && *i < (int)ft_strlen(str))
	{
		if (!ft_strchr(&str[*i], '\n'))
			return ;
		ij = ft_get_multi(*i, prp, str);
		j = ij.x;
		while (str[*i] && str[*i] != '\n')
			(*i)++;
		if (str[*i] == '\n')
			(*i)++;
		while (str[*i] && str[*i] != '\n' && j > 0)
		{
			(*i)++;
			j--;
		}
	}
}

void					ft_alt_up(int *i, char *str, int prplen, int r)
{
	t_xy				ij;
	struct winsize		wd;

	if (r == A_UP)
	{
		ij = ft_get_col_line(*i, prplen, str);
		if (r == A_UP && ij.y > 0 && str)
		{
			ioctl(0, TIOCGWINSZ, &wd);
			if (ij.y == 1 && ij.x < prplen)
				*i = 0;
			else
				*i = *i - wd.ws_col;
		}
	}
}

void					ft_alt_down(int *i, char *str, int prplen, int r)
{
	t_xy				ij;
	t_xy				xy;
	struct winsize		wd;

	if (r == A_DOWN)
	{
		ij = ft_get_col_line(*i, prplen, str);
		xy = ft_get_col_line(ft_strlen(str), prplen, str);
		if (r == A_DOWN && ij.y < xy.y && str)
		{
			ioctl(0, TIOCGWINSZ, &wd);
			if (ij.y == xy.y - 1 && ij.x > xy.x)
				*i = ft_strlen(str);
			else
				*i = *i + wd.ws_col;
		}
	}
}
