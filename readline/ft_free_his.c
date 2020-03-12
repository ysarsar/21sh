/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_his.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:05:18 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/07 00:18:31 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

void				ft_free_lst(t_auto **n)
{
	t_auto			*nd;
	t_auto			*tmp;

	nd = *n;
	while (nd)
	{
		tmp = nd->next;
		ft_strdel(&nd->data);
		free(nd);
		nd = tmp;
	}
}
