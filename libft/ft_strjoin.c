/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:21:35 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:26:03 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	lenstr;

	if (s1 && s2)
	{
		lenstr = ft_strlen((char *)s1) + ft_strlen((char *)s2);
		str = ft_strnew(lenstr);
		if (str == NULL)
			return (NULL);
		str = ft_strcpy(str, s1);
		str = ft_strcat(str, s2);
		return (str);
	}
	return (NULL);
}
