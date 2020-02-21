/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 04:59:05 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/21 15:26:17 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int			ft_quotes(char **cmd, int i, char **tmp_token)
{
	char 	*str;
	char 	*tmp;
	char	*read;
	char 	*cur;
	char 	c;
	int		j;

	str = *cmd;
	tmp = *tmp_token;
	c = str[i];
	j = 0;
	if (tmp[0] != '\0')
		j = ft_strlen(tmp);
	while (str[i] && str[++i] != c)
	{
		if ((str[i] == '\0' || str[i + 1] == '\0')&& str[i] != c)
		{
			if (c == '\'')
				read = readline("quote> ");
			else if (c == '"')
				read = readline("dquote> ");
			cur = ft_strjoin(str, "\n");
			free(str);
			str = ft_strjoin(cur, read);
			free(cur);
			free(read);
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
		while (!is_white(str[i]) && !ft_is_there("'\";|><", str[i]) && i <= ft_strlen(str) && str[i])
				tmp[j++] = str[i++];
	}
	if ((str[i] == '\'' || str[i] == '"') && !is_white(str[i + 1]) && i < ft_strlen(str))
	{
		i = ft_quotes(&str, i, &tmp);
		*cmd = str;
	}
	return (++i);
}