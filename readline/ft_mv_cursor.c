/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mv_cursor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 15:23:00 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/07 00:20:37 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

void					ft_home_end_line(char *str, int *i, int r)
{
	if (r == HOME)
		*i = 0;
	if (r == END)
		*i = ft_strlen(str);
}

void					ft_alt_left_right(char *str, int *i, int r)
{
	if (r == A_LEFT)
	{
		while (*i > 0 && !ft_isalnum(str[*i]))
			(*i)--;
		while (*i > 0 && ft_isalnum(str[*i]))
			(*i)--;
		while (*i > 0 && !ft_isalnum(str[*i]))
			(*i)--;
		if (str[*i] && *i != 0)
			(*i)++;
	}
	if (r == A_RIGHT)
	{
		while (str[*i] && !ft_isalnum(str[*i]))
			(*i)++;
		while (str[*i] && ft_isalnum(str[*i]))
			(*i)++;
	}
}

void					ft_mv_cusror(int r, int *i, char *str)
{
	if (r == LEFT && (*i > 0))
		(*i)--;
	if (r == RIGHT && *i <= (int)ft_strlen(str) - 1)
		(*i)++;
}

t_xy					ft_get_multi(int i, int len, char *str)
{
	t_xy				xy;
	int					x;
	int					y;
	int					k;
	struct winsize		ws;

	x = len;
	y = 0;
	k = 0;
	ioctl(0, TIOCGWINSZ, &ws);
	while (str[k] && k < i)
	{
		if (x >= ws.ws_col - 1 || str[k] == '\n')
		{
			x = -1;
			y++;
		}
		k++;
		x++;
	}
	xy.x = x;
	xy.y = y;
	return (xy);
}

t_xy					ft_get_col_line(int i, int len, char *str)
{
	t_xy				xy;
	int					x;
	int					y;
	int					k;
	struct winsize		ws;

	x = 0;
	y = 0;
	k = 0;
	ioctl(0, TIOCGWINSZ, &ws);
	while ((((y * ws.ws_col) + x) - len) < i)
	{
		if (x >= ws.ws_col - 1 || str[k] == '\n')
		{
			x = -1;
			y++;
		}
		k++;
		x++;
	}
	xy.x = x;
	xy.y = y;
	return (xy);
}
