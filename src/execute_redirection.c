/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 01:44:59 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/04 04:31:46 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	int		ft_agg_out(t_redirection *redir, int fd)
{
	int		left;

	if (redir->left)
		left = ft_atoi(redir->left);
	else
		left = 1;
	if (ft_is_numeric(redir->right))
		fd = ft_agg_digit(redir, fd, left);
	else if (ft_strcmp(redir->right, "-") == 0)
	{
		close(left);
		return (255);
	}
	else if (redir->right[ft_strlen(redir->right) - 1] == '-')
		fd = ft_agg_close(redir, fd, left);
	else
		fd = ft_agg_word(redir, fd, left);
	return (fd);
}

static	int		ft_agg_in(t_redirection *redir, int fd)
{
	int left;

	if (redir->left)
		left = ft_atoi(redir->left);
	else
		left = 0;
	if (ft_is_numeric(redir->right))
		fd = ft_agg_digit(redir, fd, left);
	else if (ft_strcmp(redir->right, "-") == 0)
	{
		close(left);
		return (255);
	}
	else if (redir->right[ft_strlen(redir->right) - 1] == '-')
		fd = ft_agg_close(redir, fd, left);
	else
		fd = ft_agg_word(redir, fd, left);
	return (fd);
}

static	int		ft_heredoc(t_redirection *redir, char *tty)
{
	int		fd;
	int		pip[2];
	int		tmp;

	tmp = 255;
	fd = open(tty, O_RDWR);
	dup2(fd, 0);
	dup2(1, tmp);
	dup2(fd, 1);
	close(fd);
	pipe(pip);
	ft_putstr_fd(redir->right, pip[1]);
	close(pip[1]);
	dup2(pip[0], 0);
	close(pip[0]);
	dup2(tmp, 1);
	close(tmp);
	return (255);
}

int				execute_redirection(t_redirection *redirection, char *tty)
{
	t_redirection	*current;
	int				fd;

	current = redirection;
	fd = 0;
	while (current)
	{
		if ((current->type == REDIR_OUT || current->type == REDIR_IN) &&
			(fd = ft_redir_inout(current, fd)) < 0)
			break ;
		else if (current->type == APPEND_OUT)
			fd = ft_redir_append(current, fd);
		else if (current->type == AGGREGATION_OUT &&
				(fd = ft_agg_out(current, fd)) < 0)
			break ;
		else if (current->type == AGGREGATION_IN &&
				(fd = ft_agg_in(current, fd)) < 0)
			break ;
		else if (current->type == HEREDOC)
			fd = ft_heredoc(current, tty);
		current = current->next;
	}
	return (fd);
}
