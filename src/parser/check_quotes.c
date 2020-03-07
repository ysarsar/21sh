/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 04:59:05 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/07 08:34:26 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

static	char	*ft_quote_continue(char *str, char c, t_his **his)
{
	char	*read;
	char	*cur;
	char	*ptr;

	read = NULL;
	ptr = str;
	if (c == '\'')
		read = my_readline(his, "quote> ");
	else if (c == '"')
		read = my_readline(his, "dquote> ");
	cur = ft_strjoin(ptr, "\n");
	free(ptr);
	ptr = ft_strjoin(cur, read);
	free_str(cur, read);
	return (ptr);
}

static	int		ft_quote_continue2(t_quote_var v, char *str, char **tmp, int i)
{
	char *ptr;

	ptr = *tmp;
	if (str[i] == v.c && !is_white(str[i + 1]))
	{
		i++;
		while (!is_white(str[i]) && !ft_is_there("'\";|><", str[i]) && str[i])
			ptr[v.j++] = str[i++];
	}
	*tmp = ptr;
	return (i);
}

int				ft_quotes(char **cmd, int i, char **tmp_token, t_his **his)
{
	char		*str;
	char		*tmp;
	t_quote_var	var;

	str = *cmd;
	tmp = *tmp_token;
	var.c = str[i];
	var.j = 0;
	if (tmp[0] != '\0')
		var.j = ft_strlen(tmp);
	while (str[i] && str[++i] != var.c)
	{
		if ((str[i] == '\0' || str[i + 1] == '\0') && str[i] != var.c)
			str = ft_quote_continue(str, var.c, his);
		*cmd = str;
		tmp[var.j++] = (str[i] == '\0' || str[i + 1] == '\0') ? '\n' : str[i];
	}
	i = ft_quote_continue2(var, str, &tmp, i);
	if (ft_is_there(";|><", str[i]))
		return (i);
	if ((str[i] == '\'' || str[i] == '"') && !is_white(str[i + 1]))
		i = ft_quotes(&str, i, &tmp, his);
	*cmd = str;
	return (++i);
}
