/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:21:41 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:26:05 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t srclen;
	size_t destlen;
	size_t w;

	srclen = ft_strlen(src);
	destlen = ft_strlen((const char *)dest);
	if (destlen >= size)
		srclen = srclen + size;
	else
		srclen = srclen + destlen;
	w = 0;
	while (src[w] != '\0' && destlen + 1 < size)
	{
		dest[destlen] = src[w];
		destlen++;
		w++;
	}
	dest[destlen] = '\0';
	return (srclen);
}
