/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_and_del_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 23:38:26 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/07 00:18:54 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

size_t			ft_del_char(char *str, int *i, int r)
{
	int			ii;
	char		tmp;

	if (r == DEL && *i > 0)
	{
		ii = (*i) - 1;
		if (str)
		{
			while (str[ii])
			{
				tmp = str[ii + 1];
				str[ii] = str[ii + 1];
				str[ii + 1] = tmp;
				ii++;
			}
		}
		(*i)--;
	}
	return (0);
}

void			ft_charjoin(char **s, char *buff, int *i)
{
	char		*rest;
	char		*line;
	char		*str;
	int			index;

	if (ft_isprint(buff[0]))
	{
		index = *i;
		str = *s;
		rest = ft_strdup(&str[index]);
		ft_strclr(&str[index]);
		line = ft_strjoin(str, buff);
		*s = ft_strjoin(line, rest);
		ft_strdel(&rest);
		ft_strdel(&str);
		ft_strdel(&line);
		*i = *i + ft_strlen(buff);
	}
}
