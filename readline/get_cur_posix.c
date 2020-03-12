/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cur_posix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 14:55:32 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/07 00:21:43 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

void		clean_posx_str(char *buff)
{
	char	*str;
	int		j;
	int		i;

	i = 0;
	j = 0;
	str = ft_strdup(buff);
	while (!ft_isdigit(str[i]) && str[i])
		i++;
	while (ft_isdigit(str[i]) && str[i])
		buff[j++] = str[i++];
	buff[j] = '\0';
	g_pos.y = ft_atoi(buff);
	j = 0;
	ft_strclr(buff);
	while (!ft_isdigit(str[i]) && str[i])
		i++;
	while (ft_isdigit(str[i]) && str[i])
		buff[j++] = str[i++];
	g_pos.x = ft_atoi(buff);
	ft_strdel(&str);
}

void		get_cur_position(void)
{
	char	buff[21];

	buff[20] = 0;
	while (!ft_isdigit(buff[2]))
	{
		ft_putstr_fd("\e[6n", 0);
		read(0, buff, 20);
	}
	clean_posx_str(buff);
}
