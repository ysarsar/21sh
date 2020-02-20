/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:05:51 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/20 17:19:37 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int			check_syntax(t_parse *ast)
{
	t_parse		*current;

	current = ast;
	while (current)
	{
		if (current->redirection)
			check_redirection_syntax(current->redirection);
		if (current->pipe)
			check_pipe_syntax(current->pipe);
		if (!current->cmd)
			return (0);
		current = current->sep;
	}
	return (1);
}