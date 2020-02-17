/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:22:31 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:26:13 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char		*ft_strndup(const char *s1, size_t n)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(*str) * (n + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && n)
	{
		str[i] = s1[i];
		i++;
		n--;
	}
	str[i] = '\0';
	return (str);
}
