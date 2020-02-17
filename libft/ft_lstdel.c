/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:17:03 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:25:21 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*next_lst;
	t_list	*list;

	list = *alst;
	while (list != NULL)
	{
		next_lst = list->next;
		del(list->content, list->content_size);
		ft_memdel((void**)&list);
		list = next_lst;
	}
	*alst = NULL;
}
