/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_press_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 13:54:01 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/07 00:20:51 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

void			ft_cursor_motion(int *i, char *buff, char **str, char *prp)
{
	if (ft_strchr(*str, '\n'))
	{
		ft_alt_up_multi(i, *str, (*(unsigned int*)buff), ft_strlen(prp));
		ft_alt_down_multi(i, *str, (*(unsigned int*)buff), ft_strlen(prp));
	}
	else
	{
		ft_alt_up(i, *str, ft_strlen(prp), (*(unsigned int*)buff));
		ft_alt_down(i, *str, ft_strlen(prp), (*(unsigned int*)buff));
	}
	ft_alt_left_right(*str, i, (*(unsigned int*)buff));
	ft_home_end_line(*str, i, (*(unsigned int*)buff));
	ft_mv_cusror((*(unsigned int*)buff), i, *str);
}

int				ft_press_key(int *i, char *buff, char **str, t_his **ht)
{
	ft_save_cmd((*(unsigned int*)buff), *str);
	ft_paste(str, (*(unsigned int*)buff), i);
	if (buff[0] == 9)
		comp(str);
	if (ht && *ht)
		if (((*(unsigned int*)buff) == UP || (*(unsigned int*)buff) == DOWN))
			ft_go_up_down((*(unsigned int*)buff), str, ht);
	ft_del_char(*str, i, (*(unsigned int*)buff));
	ft_charjoin(str, buff, i);
	if ((*(unsigned int*)buff) == UP ||
			(*(unsigned int*)buff == DOWN || buff[0] == 9))
		*i = ft_strlen(*str);
	if ((*(unsigned int*)buff) == ENTR)
		return (-1);
	return (0);
}

void			ft_befor_return(char **str, int line, int prplent, int r)
{
	int			i;
	t_xy		xy;

	i = ft_strlen(*str);
	if (ft_strchr(*str, '\n'))
		xy = ft_get_multi(i, prplent, *str);
	else
		xy = ft_get_col_line(i, prplent, *str);
	ft_goto(xy.x, line + xy.y - 1);
	tputs(tgetstr("cd", NULL), 0, ft_putsfd);
	ft_putstr("\n");
	if (r == 4)
		*str[0] = -6;
}
