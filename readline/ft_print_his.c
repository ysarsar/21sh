/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_his.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:07:07 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/07 00:21:02 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

int						ft_max_lent(t_auto *comp)
{
	int					i;
	int					lent;

	i = 0;
	while (comp && comp->next)
	{
		if (i < (lent = ft_strlen(comp->data)))
			i = lent;
		comp = comp->next;
	}
	return (i);
}

void					ft_print_colors(char *name)
{
	struct stat			type;

	lstat(name, &type);
	if (S_ISLNK(type.st_mode))
		ft_put4str(NULL, "\033[1;35m", name, "\033[0m");
	else if (S_ISDIR(type.st_mode))
		ft_put4str(NULL, "\033[1;36m", name, "\033[0m");
	else if (!S_ISDIR(type.st_mode) && type.st_mode & S_IXOTH)
		ft_put4str(NULL, "\033[1;31m", name, "\033[0m");
	else
		ft_putstr(name);
}

void					ft_print_argss(t_auto *comp)
{
	int					maxlent;
	struct winsize		w;
	int					i;
	int					j;

	ioctl(1, TIOCGWINSZ, &w);
	i = 0;
	j = g_pos.y;
	maxlent = ft_max_lent(comp);
	while (comp && comp->next && j < w.ws_row)
	{
		if ((i + maxlent) > w.ws_col)
		{
			i = 0;
			j++;
		}
		tputs(tgoto(tgetstr("cm", NULL), i, j), 0, ft_putsfd);
		ft_print_colors(comp->data);
		i = i + maxlent + 1;
		comp = comp->next;
	}
	tputs(tgoto(tgetstr("cm", NULL), i, j + 1), 0, ft_putsfd);
}
