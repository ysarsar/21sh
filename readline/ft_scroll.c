/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scroll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 23:34:12 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/07 00:21:33 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

void					ft_scroll(char *str, char *prp)
{
	int					i;
	struct winsize		w;
	t_xy				xy;

	ioctl(1, TIOCGWINSZ, &w);
	if (ft_strchr(str, '\n'))
		xy = ft_get_multi(ft_strlen(str), ft_strlen(prp), str);
	else
		xy = ft_get_col_line(ft_strlen(str), ft_strlen(prp), str);
	if (w.ws_row < xy.y + g_pos.y ||
			(w.ws_row == xy.y + g_pos.y && xy.x == w.ws_col))
		i = xy.y + g_pos.y - w.ws_row;
	else
		return ;
	while (i > 0)
	{
		tputs(tgetstr("do", NULL), 0, ft_putsfd);
		i--;
	}
	get_cur_position();
	g_pos.y = g_pos.y - xy.y;
	g_pos.x = 0;
}
