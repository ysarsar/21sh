/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 18:23:12 by ysarsar           #+#    #+#             */
/*   Updated: 2019/12/11 18:26:21 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			word_count(char *s, char c)
{
	int				i;
	int				res;

	i = 0;
	res = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i + 1] == c)
			res++;
		i++;
	}
	if (s[i] == '\0' && s[i - 1] != c)
		res++;
	return (res);
}

static int			word_len(char *s, char c)
{
	int				len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char				**ft_strsplit(char const *s, char c)
{
	int			word_countx;
	char		**str;
	int			i;

	if (!s)
		return (NULL);
	word_countx = word_count((char *)s, c);
	str = (char**)malloc(sizeof(char*) * word_countx + 1);
	i = 0;
	if (!str)
		return (NULL);
	while (word_countx-- && *s)
	{
		while (*s == c && *s != '\0')
			s++;
		str[i] = ft_strsub((char *)s, 0, word_len((char*)s, c));
		if (!str[i])
			return (NULL);
		s = s + word_len((char *)s, c);
		i++;
	}
	str[i] = 0;
	return (str);
}
