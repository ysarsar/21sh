/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 00:41:29 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/07 01:05:13 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

void			ft_free_his(t_his **his)
{
	t_his *nd;
	t_his *tmp;

	if (*his && his)
	{
		nd = *his;
		while (nd && nd->prev)
			nd = nd->prev;
		while (nd)
		{
			tmp = nd->next;
			ft_strdel(&nd->data);
			free(nd);
			nd = tmp;
		}
	}
}

void			ft_save_cmd(int r, char *cmd)
{
	if ((r == UP || r == DOWN) && g_last_his == 0)
	{
		if (g_cmd)
			ft_strdel(&g_cmd);
		g_cmd = ft_strdup(cmd);
	}
	if (r == UP || r == DOWN)
		g_last_his++;
}

void			ft_new_his(t_his **ht)
{
	if (!ht)
		return ;
	*ht = (t_his *)malloc(sizeof(t_his));
	(*ht)->next = NULL;
	(*ht)->data = NULL;
	(*ht)->prev = NULL;
}

t_his			*ft_add_his(t_his **ht, char *cmd)
{
	t_his		*tmp;
	t_his		*new;

	if (!ht || !cmd)
		return (NULL);
	if (!*ht)
	{
		ft_new_his(ht);
		if (*ht)
			(*ht)->data = ft_strdup(cmd);
		return (*ht);
	}
	tmp = *ht;
	while (tmp->next)
		tmp = tmp->next;
	ft_new_his(&new);
	new->data = ft_strdup(cmd);
	new->prev = tmp;
	tmp->next = new;
	return (new);
}

void			ft_go_up_down(int i, char **str, t_his **last)
{
	if (i == DOWN && *last && !(*last)->next)
	{
		ft_strdel(str);
		*str = ft_strdup(g_cmd);
		g_last_his = 0;
		g_first = 0;
		return ;
	}
	else if (i == UP && *last)
	{
		if (g_first == 1)
			if ((*last)->prev != NULL)
				*last = (*last)->prev;
		ft_strdel(str);
		*str = ft_strdup((*last)->data);
	}
	else if (i == DOWN && *last)
	{
		if (g_first == 1)
			if ((*last)->next != NULL)
				*last = (*last)->next;
		ft_strdel(str);
		*str = ft_strdup((*last)->data);
	}
	g_first = 1;
}
