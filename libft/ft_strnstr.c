/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:22:52 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:26:19 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t i;

	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack && n)
	{
		if (*haystack == *needle)
		{
			i = 0;
			while (*(haystack + i) == *(needle + i)
			&& *(haystack + i) && *(needle + i) && i < n)
				i++;
			if (*(needle + i) == '\0')
				return ((char *)haystack);
		}
		haystack++;
		n--;
	}
	return (NULL);
}
