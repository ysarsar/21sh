/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenz_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 22:00:03 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/21 15:26:44 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

int		ft_separators(t_token **tok, char *str, int i)
{
	t_token	*token;

	token = *tok;
	token->value = ft_strsub(str, i, 1);
	if (str[i] == ';')
		token->type = SEPARATEUR;
	else if (str[i] == '|')
		token->type = PIPE;
	return (i + 1);
}

int		is_white(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int		ft_redirection(char *str, t_token **tok, int i, int *redir)
{
	t_token *token;

	token = *tok;
	if (*redir || str[i] == '&')
	{
		*redir = 0;
		return (-1);
	}
	if (str[i] == '>')
	{
		if (str[i + 1] == '&')
		{
			token->type = AGGREGATION_OUT;
			i++;
		}
		else if (str[i + 1] == '>')
		{
			token->type = APPEND_OUT;
			i++;
		}
		else
			token->type = REDIR_OUT;
	}
	else if (str[i] == '<')
	{
		if (str[i + 1] == '&')
		{
			token->type = AGGREGATION_IN;
			i++;
		}
		else if (str[i + 1] == '<')
		{
			token->type = HEREDOC;
			i++;
		}
		else
			token->type = REDIR_IN;
	}
	*redir = 1;
	return (i + 1);
}

int		ft_is_numeric(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		ft_check_fd(char *str, char **tmp, t_token **token, int i, int mode)
{
	t_token		*tok;

	tok = *token;
	if (str[i - 1] > 32 && ft_is_numeric(*tmp) && !mode)
		tok->type = L_FD;
	else if (mode)
		tok->type = R_FD;
	else
		tok->type = WORD;
	tok->value = *tmp; 
	return (1);
}

int		ft_check_word(t_token **token, char **tmp)
{
	t_token *tok;
	char *str;

	tok = *token;
	str = *tmp;
	tok->value = str;
	tok->type = WORD;
	return (1);
}
