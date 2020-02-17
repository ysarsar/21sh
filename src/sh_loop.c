/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 23:02:07 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/18 00:43:24 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	void	free_ast(t_parse **ast)
{
	t_parse		*curr;
	t_parse		*next;

	curr = *ast;
	while (curr)
	{
		if (curr->cmd)
			free(curr->cmd);
		next = curr->sep;
		free(curr);
		curr = next;
	}
	*ast = NULL;
}

void		sh_loop(t_env **envp)
{
	int		status;
	char	*line;
	t_parse	*ast;
	t_parse	*root;

	status = 1;
	ast = NULL;
	line = NULL;
	while (status)
	{
		if ((line = readline("\033[0;32m$> \033[0m")) != NULL)
		{
			ast = ft_parse_tree(&line);
			root = ast;
			while (ast)
			{
				printf("[ %s ]\n", ast->cmd);
				if (strncmp("exit", &(ast->cmd[0]), 4) == 0)
					exit(0);
				ast = ast->sep;
			}
			//status = sh_execute(&ast, envp);
			free_ast(&root);
		}
		ft_strdel(&line);
	}
}