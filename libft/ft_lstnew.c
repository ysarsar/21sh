/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:17:39 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:25:26 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new_list;

	new_list = (t_list*)ft_memalloc(sizeof(t_list));
	if (new_list == NULL)
		return (NULL);
	if (content != NULL)
	{
		new_list->content = ft_memalloc(content_size);
		ft_memcpy(new_list->content, content, content_size);
		new_list->content_size = content_size;
	}
	else if (content == NULL)
	{
		new_list->content = NULL;
		new_list->content_size = 0;
	}
	new_list->next = NULL;
	return (new_list);
}
