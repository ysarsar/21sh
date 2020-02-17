/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:18:55 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:25:36 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*psrc;
	char		*pdest;

	psrc = src;
	pdest = dest;
	if (pdest < psrc)
	{
		dest = ft_memcpy(dest, src, n);
		return (dest);
	}
	else
	{
		pdest = dest + n - 1;
		psrc = src + n - 1;
		while (n--)
		{
			*pdest-- = *psrc--;
		}
		return (dest);
	}
	return (dest);
}
