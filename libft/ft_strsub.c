/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:24:17 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:26:22 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	int		i;

	if (s)
	{
		i = 0;
		str = (char *)malloc(sizeof(*str) * (len + 1));
		if (str == NULL)
			return (NULL);
		while (s[start] != '\0' && len--)
		{
			str[i] = s[start];
			i++;
			start++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
