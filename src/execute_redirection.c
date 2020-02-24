/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 01:44:59 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/24 01:04:48 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	int	ft_redir_inout(t_redirection *redirect, int fd)
{
	int		left;
	if (fd)
		close(fd);
	if (redirect->type == REDIR_OUT)
		fd = open(redirect->right, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
	{
		fd = open(redirect->right, O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("21sh: ", 2);
			ft_putstr_fd(redirect->right, 2);
			ft_putendl_fd(": No such file or directory", 2);
			return (fd);
		}
	}
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

static	int	ft_redir_append(t_redirection *redir, int fd)
{
	int		left;
	if (fd)
		close(fd);
	fd = open(redir->right, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (redir->left)
	{
		left = ft_atoi(redir->left);
		dup2(fd, left);
	}
	else
		dup2(fd, 1);
	return (fd);
}

static	int	ft_agg_out(t_redirection *redir, int fd)
{
	int		left;
	char	*file_d;

	if (fd)
		close(fd);
	if (!check_fd(redir->right))
		return (-1);
	if (ft_is_numeric(redir->right))
	{
		fd = ft_atoi(redir->right);
		if (redir->left)
		{
			left = ft_atoi(redir->left);
			dup2(fd, left);
		}
		else
			dup2(fd, 1);
	}
	else
	{
		if (redir->left)
		{
			left = ft_atoi(redir->left);
			if (redir->right[0] == '-')
				close(left);
			else
			{
				file_d = ft_strsub(redir->right, 0, ft_strlen(redir->right) - 1);
				fd = ft_atoi(file_d);
				dup2(fd, 1);
				close(fd);
			}
		}
		else
			close(1);
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
		{
			if ((fd = ft_redir_inout(current, fd)) < 0)
				break;
		}
		else if (current->type == APPEND_OUT)
			fd = ft_redir_append(current, fd);
		else if (current->type == AGGREGATION_OUT)
		{
			if ((fd = ft_agg_out(current, fd)) < 0)
				break;
		}
		current = current->next;
	}
	return (fd);
}
