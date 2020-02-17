/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:22:10 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:26:10 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	size_t	s1len;
	char	*ps1;

	s1len = ft_strlen((const char *)s1);
	ps1 = s1 + s1len;
	while (n > 0 && *s2)
	{
		*ps1++ = *s2++;
		n--;
	}
	*ps1 = '\0';
	return (s1);
}
