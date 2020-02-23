/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 01:44:59 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/23 20:50:30 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	int	ft_redir_inout(t_redirection *redirect, int fd)
{
	int		left;
	if (fd)
		close(fd);
	fd = open(redirect->right, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redirect->left)
	{
		left = ft_atoi(redirect->left);
		dup2(fd, left);
	}
	else
	{
		if (redirect->type == REDIR_OUT)
			dup2(fd, 1);
		else
			dup2(fd, 0);
	}
	return (fd);
}

int			execute_redirection(t_redirection *redirection)
{
	t_redirection 	*current;
	int				fd;
	int				left;
	int				right;
	
	current = redirection;
	fd = 0;
	while (current)
	{
		if (current->type == REDIR_OUT || current->type == REDIR_IN)
			fd = ft_redir_inout(current, fd);	
		current = current->next;
	}
	return (fd);
}
