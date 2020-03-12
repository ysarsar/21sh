/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 22:34:17 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/07 12:48:18 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

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

char		*ft_document(char *redir_right)
{
	char	*heredoc;
	char	*text;
	char	*ptr;
	char	*tmp;
	int		c;

	c = 0;
	text = NULL;
	while (ft_strcmp((heredoc = my_readline(NULL, "> ")), redir_right) != 0)
	{
		if (heredoc[0] == -6)
			break ;
		tmp = ft_strjoin(heredoc, "\n");
		if (!c && (text = tmp))
			c = 1;
		else
		{
			ptr = text;
			text = ft_strjoin(ptr, tmp);
			free_str(ptr, tmp);
		}
		ft_strdel(&heredoc);
	}
	ft_strdel(&heredoc);
	return (text);
}

static	int	ft_heredoc(t_token *token, t_redirection **redir)
{
	char	*heredoc;

	heredoc = ft_document(token->value);
	if (heredoc)
	{
		ft_strdel(&(*redir)->right);
		(*redir)->right = heredoc;
	}
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
	{
		(*redir)->right = ft_strdup(token->value);
		if ((*redir)->type == HEREDOC)
			ft_heredoc(token, redir);
	}
	else
		(*redir)->type = token->type;
	return (1);
}
