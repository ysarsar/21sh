/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 22:22:04 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/01 08:31:56 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh.h"

static	void	free_all_struct(t_token *token, t_parse *ast)
{
	if (token->value)
		ft_strdel(&token->value);
	if (token)
		free(token);
	if (ast)
		free_ast(&ast);
}

t_parse			*ft_parse_tree(char **line)
{
	t_token		*token;
	t_parse		*ast;
	t_parse		*current;
	int			i;

	token = NULL;
	ast = NULL;
	current = NULL;
	ft_next_token(line, &token, 0);
	while ((i = ft_next_token(line, &token, 1)) > 0)
	{
		if (!(ast))
		{
			if (!(ast = (t_parse*)ft_memalloc(sizeof(t_parse))))
				return (NULL);
			current = ast;
		}
		if (token->type == WORD)
			ft_word_type(&ast, &token);
		else if (token->type == SEPARATEUR)
		{
			if (!ft_separateur_type(&ast, current, token))
			{
				free_all_struct(token, current);
				return (NULL);
			}
		}
		else if (token->type == PIPE)
		{
			if (!ft_pipe_type(&ast, token))
			{
				free_all_struct(token, current);
				return (NULL);
			}
		}
		else if (token->type == L_FD || token->type == R_FD)
			ft_redirection_type(&ast, token);
		else
			ft_redirection_type(&ast, token);
		free_all_struct(token, NULL);
	}
	if (i < 0)
	{
		ft_putendl_fd("21sh: parse error", 2);
		free_all_struct(token, current);
		return (NULL);
	}
	free_all_struct(token, NULL);
	return (current);
}
