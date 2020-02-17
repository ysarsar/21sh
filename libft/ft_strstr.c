/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:23:25 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:26:21 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t i;

	if (needle[0] == '\0')
		return ((char *)haystack);
	while (*haystack != '\0')
	{
		if (*haystack == *needle)
		{
			i = 0;
			while (*(haystack + i) == *(needle + i) &&
			*(haystack + i) && *(needle + i))
				i++;
			if (*(needle + i) == '\0')
				return ((char *)haystack);
		}
		haystack++;
	}
	return (NULL);
}
