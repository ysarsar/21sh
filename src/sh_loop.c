/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 23:02:07 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/07 10:11:18 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	int		sh_loop2(char **line, t_his **his, t_parse **tree, t_env **envp)
{
	int		status;
	char	*tty;
	t_parse	*ast;

	status = 0;
	tty = ttyname(0);
	*tree = ft_parse_tree(line, his);
	if (line && *line)
		ft_add_his(his, *line);
	ast = *tree;
	if (*envp)
		if (check_syntax(ast))
			status = sh_execute(&ast, envp, tty);
	return (status);
}

static	void	free_loop(t_parse **ast, char **line)
{
	if (g_cmd)
		ft_strdel(&g_cmd);
	free_ast(ast);
	ft_strdel(line);
}

void			sh_loop(t_env **envp)
{
	int		status;
	char	*line;
	t_parse	*ast;
	t_his	*his;

	status = 1;
	ast = NULL;
	his = NULL;
	if ((ttyname(0)))
	{
		while (status)
		{
			if (((line = my_readline(&his, "21sh-1.0$ ")) != NULL) && line[0])
			{
				if (line[0] != -6)
					status = sh_loop2(&line, &his, &ast, envp);
				else
					status = 0;
			}
			else
				return ;
			free_loop(&ast, &line);
		}
		ft_free_his(&his);
	}
}
