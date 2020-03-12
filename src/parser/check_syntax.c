/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:05:51 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/07 12:42:27 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

static	int	check_redirection_syntax(t_redirection *redirection)
{
	t_redirection	*redir;

	redir = redirection;
	while (redir)
	{
		if (!redir->right)
		{
			ft_putendl_fd("21sh: syntax error near unexpected token", 2);
			return (1);
		}
		redir = redir->next;
	}
	return (0);
}

static	int	check_pipe_syntax(t_parse *ast)
{
	t_parse *current;

	current = ast;
	while (current)
	{
		if (current->redirection)
		{
			if (check_redirection_syntax(current->redirection))
				return (1);
		}
		if (!current->cmd)
		{
			ft_putendl_fd("21sh: syntax error near unexpected token", 2);
			return (1);
		}
		current = current->pipe;
	}
	return (0);
}

int			check_syntax(t_parse *ast)
{
	t_parse		*current;

	current = ast;
	if (!current)
		return (0);
	while (current)
	{
		if (current->pipe)
		{
			if (check_pipe_syntax(current))
				return (0);
		}
		else if (!current->cmd)
		{
			ft_putendl_fd("21sh: syntax error near unexpected token", 2);
			return (0);
		}
		if (current->redirection)
		{
			if (check_redirection_syntax(current->redirection))
				return (0);
		}
		current = current->sep;
	}
	return (1);
}
