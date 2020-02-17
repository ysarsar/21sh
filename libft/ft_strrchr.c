/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:23:00 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:26:20 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *ps;

	ps = (char *)s + ft_strlen(s);
	while (ps >= s)
	{
		if (*ps == (char)c)
			return (ps);
		ps--;
	}
	return (NULL);
}
