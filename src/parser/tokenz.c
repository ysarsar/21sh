/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenz.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 02:38:21 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/03 01:09:03 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

static	void	ft_next_token2(char **line, int *i, t_token **tok, int *redir)
{
	int		j;
	char	*tmp;
	char	*str;
	t_token	*token;
	int		k;

	j = 0;
	k = *i;
	str = *line;
	token = *tok;
	if (!(tmp = ft_strnew(1024)))
		return ;
	while (str[k] && !is_white(str[k]) && !ft_is_there("'\";|><", str[k]))
		tmp[j++] = str[k++];
	if ((str[k] == '\'' || str[k] == '"') && (k = ft_quotes(&str, k, &tmp)))
		*line = str;
	if (str[k] == '>' || str[k] == '<')
		ft_check_fd(str, &tmp, &token, k, 0);
	else if (*redir && !(*redir = 0))
		ft_check_fd(str, &tmp, &token, k, 1);
	else if (tmp[0])
		ft_check_word(&token, &tmp);
	free(tmp);
	*i = k;
}

int				ft_next_token(char **line, t_token **tok, int mode)
{
	char		*str;
	static	int	i = 0;
	static	int	redir = 0;
	t_token		*token;

	if (!mode)
	{
		redir = 0;
		return (i = 0);
	}
	if (!(*tok = (t_token*)ft_memalloc(sizeof(t_token))))
		return (0);
	token = *tok;
	str = *line;
	while (str[i])
	{
		if (str[i] == ';' || str[i] == '|')
		{
			i = ft_separators(&token, str, i);
			return (1);
		}
		else if (str[i] == '<' || str[i] == '>' || str[i] == '&')
			return (i = ft_redirection(str, &token, i, &redir));
		else if (str[i] && !is_white(str[i]))
		{
			ft_next_token2(&str, &i, &token, &redir);
			*line = str;
			return (1);
		}
		else
			i++;
	}
	*line = str;
	return (0);
}
