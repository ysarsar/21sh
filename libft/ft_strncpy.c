/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:22:25 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:26:12 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char *dest;

	dest = dst;
	while (*src != '\0' && len > 0)
	{
		*dest++ = *src++;
		len--;
	}
	while (len > 0)
	{
		*dest++ = '\0';
		len--;
	}
	return (dst);
}
