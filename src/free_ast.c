/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 10:03:58 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/07 10:06:52 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	void	free_redirection(t_redirection **redir)
{
	t_redirection	*redirection;
	t_redirection	*next;

	redirection = *redir;
	while (redirection)
	{
		next = redirection->next;
		if (redirection->left)
			ft_strdel(&redirection->left);
		if (redirection->right)
			ft_strdel(&redirection->right);
		free(redirection);
		redirection = next;
	}
}

static	void	free_pipe(t_parse **root)
{
	t_parse		*current;
	t_parse		*next;

	current = *root;
	while (current)
	{
		if (current->redirection)
			free_redirection(&current->redirection);
		if (current->cmd)
			ft_strdel(&current->cmd);
		next = current->pipe;
		free(current);
		current = next;
	}
}

void			free_ast(t_parse **ast)
{
	t_parse		*curr;
	t_parse		*next;

	curr = *ast;
	while (curr)
	{
		if (curr->redirection)
			free_redirection(&curr->redirection);
		if (curr->pipe)
			free_pipe(&curr->pipe);
		if (curr->cmd)
			ft_strdel(&curr->cmd);
		next = curr->sep;
		free(curr);
		curr = next;
	}
	*ast = NULL;
}
