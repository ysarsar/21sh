/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 04:59:05 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/01 08:19:09 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

static	char	*ft_quote_continue(char *str, char c)
{
	char	*read;
	char	*cur;
	char	*ptr;

	ptr = str;
	if (c == '\'')
		read = readline("quote> ");
	else if (c == '"')
		read = readline("dquote> ");
	cur = ft_strjoin(ptr, "\n");
	free(ptr);
	ptr = ft_strjoin(cur, read);
	free_str(cur, read);
	return (ptr);
}

int				ft_quotes(char **cmd, int i, char **tmp_token)
{
	char	*str;
	char	*tmp;
	char	c;
	int		j;

	str = *cmd;
	tmp = *tmp_token;
	c = str[i];
	j = 0;
	if (tmp[0] != '\0')
		j = ft_strlen(tmp);
	while (str[i] && str[++i] != c)
	{
		if ((str[i] == '\0' || str[i + 1] == '\0') && str[i] != c)
		{
			str = ft_quote_continue(str, c);
			*cmd = str;
		}
		if (str[i] == '\0' || str[i + 1] == '\0')
			tmp[j++] = '\n';
		else
			tmp[j++] = str[i];
	}
	if (str[i] == c && !is_white(str[i + 1]))
	{
		i++;
		while (!is_white(str[i]) &&
			!ft_is_there("'\";|><", str[i]) && i <= ft_strlen(str) && str[i])
			tmp[j++] = str[i++];
	}
	if (ft_is_there(";|><", str[i]))
		return (i);
	if ((str[i] == '\'' || str[i] == '"') &&
		!is_white(str[i + 1]) && i < ft_strlen(str))
		i = ft_quotes(&str, i, &tmp);
	*cmd = str;
	return (++i);
}
