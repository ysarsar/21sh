/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 22:34:17 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/01 08:22:42 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

void		ft_word_type(t_parse **ast, t_token **tok)
{
	t_parse		*current;
	t_token		*token;
	char		*tmp;

	current = *ast;
	token = *tok;
	if (!(current->cmd))
	{
		if (token->value)
			current->cmd = ft_strdup(token->value);
		else
			current->cmd = ft_strnew(1);
	}
	else
	{
		if (token->value)
		{
			tmp = ft_strjoin(current->cmd, " ");
			free(current->cmd);
			tmp[ft_strlen(tmp) - 1] = -1;
			current->cmd = ft_strjoin(tmp, token->value);
			ft_strdel(&tmp);
		}
	}
	*ast = current;
}

int			ft_separateur_type(t_parse **ast, t_parse *current, t_token *token)
{
	t_parse		*cur;

	cur = *ast;
	if (!(cur->cmd))
	{
		ft_putendl_fd("21sh: parse error", 2);
		ft_strdel(&token->value);
		return (0);
	}
	cur = current;
	while (cur->sep)
		cur = cur->sep;
	if (!(cur->sep = (t_parse*)ft_memalloc(sizeof(t_parse))))
		return (0);
	*ast = cur->sep;
	return (1);
}

int			ft_pipe_type(t_parse **ast, t_token *token)
{
	t_parse		*cur;

	cur = *ast;
	if (!(cur->cmd))
	{
		ft_putendl_fd("21sh: parse error", 2);
		ft_strdel(&token->value);
		return (0);
	}
	if (!(cur->pipe = (t_parse*)ft_memalloc(sizeof(t_parse))))
		return (0);
	*ast = cur->pipe;
	return (1);
}

int			ft_redirection_type(t_parse **ast, t_token *token)
{
	t_parse			*current;
	t_redirection	**redir;

	current = *ast;
	redir = &current->redirection;
	while (*redir && (*redir)->right)
		redir = &(*redir)->next;
	if (!(*redir))
	{
		if (!(*redir = (t_redirection*)ft_memalloc(sizeof(t_redirection))))
			return (0);
	}
	if (token->type == L_FD)
		(*redir)->left = ft_strdup(token->value);
	else if (token->type == R_FD)
		(*redir)->right = ft_strdup(token->value);
	else
		(*redir)->type = token->type;
	return (1);
}
