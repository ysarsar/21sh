/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 22:22:04 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/04 04:41:14 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

static	int		free_all_struct(t_token *token, t_parse *ast)
{
	if (token->value)
		ft_strdel(&token->value);
	if (token)
		free(token);
	if (ast)
		free_ast(&ast);
	return (0);
}

static	int		ft_parse_tree2(t_token **tok, t_parse **ast_r, t_parse *current)
{
	t_parse		*ast;
	t_token		*token;

	ast = *ast_r;
	token = *tok;
	if (token->type == WORD)
		ft_word_type(&ast, &token);
	else if (token->type == SEPARATEUR)
	{
		if (!ft_separateur_type(&ast, current, token))
			return (free_all_struct(token, current));
	}
	else if (token->type == PIPE)
	{
		if (!ft_pipe_type(&ast, token))
			return (free_all_struct(token, current));
	}
	else if (token->type == L_FD || token->type == R_FD)
		ft_redirection_type(&ast, token);
	else
		ft_redirection_type(&ast, token);
	*ast_r = ast;
	*tok = token;
	free_all_struct(token, NULL);
	return (1);
}

static	t_parse	*print_err(t_token *token, t_parse *current)
{
	ft_putendl_fd("21sh: syntax error near unexpected token", 2);
	free_all_struct(token, current);
	return (NULL);
}

t_parse			*ft_parse_tree(char **line, t_his **his)
{
	t_token		*token;
	t_parse		*ast;
	t_parse		*current;
	int			i;

	token = NULL;
	ast = NULL;
	current = NULL;
	ft_next_token(line, &token, 0, his);
	while ((i = ft_next_token(line, &token, 1, his)) > 0)
	{
		if (!(ast))
		{
			if (!(ast = (t_parse*)ft_memalloc(sizeof(t_parse))))
				return (NULL);
			current = ast;
		}
		if (!ft_parse_tree2(&token, &ast, current))
			return (NULL);
	}
	if (i < 0)
		return (print_err(token, current));
	free_all_struct(token, NULL);
	return (current);
}
