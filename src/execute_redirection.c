/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 01:44:59 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/29 06:01:06 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	int		ft_redir_inout(t_redirection *redirect, int fd)
{
	int		left;

	if (redirect->type == REDIR_OUT)
		fd = open(redirect->right, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
	{
		fd = open(redirect->right, O_RDONLY);
		if (fd < 0)
			return (redirect_error(redirect));
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

static	int		ft_redir_append(t_redirection *redir, int fd)
{
	int		left;

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

static	int		ft_agg_digit(t_redirection *redir, int fd, int left)
{
	fd = ft_atoi(redir->right);
	if (fd != left)
	{
		if (dup2(fd, left) < 0)
		{
			printf("21sh: %d: Bad file descriptor\n", fd);
			return (-1);
		}
	}
	return (fd);
}

static	int		ft_agg_close(t_redirection *redir, int fd, int left)
{
	char *file_d;

	file_d = ft_strsub(redir->right, 0, ft_strlen(redir->right) - 1);
	fd = ft_atoi(file_d);
	if (fd != left)
	{
		ft_strdel(&file_d);
		if ((fd = ft_agg_digit(redir, fd, left)) < 0)
			return (-1);
		close(fd);
	}
	return (fd);
}

static	int		ft_agg_word(t_redirection *redir, int fd, int left)
{
	fd = open(redir->right, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd != left)
	{
		dup2(fd, left);
		if (!redir->left)
			dup2(fd, 2);
	}
	return (fd);
}

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

static	char	*ft_document(t_redirection *redir)
{
	char 	*heredoc;
	char 	*text;
	char	*ptr;
	char	*tmp;
	int		c;

	c = 0;
	while (ft_strcmp((heredoc = readline("> ")), redir->right) != 0)
	{
		tmp = ft_strjoin(heredoc, "\n");
		if (!c)
		{
			text = tmp;
			c = 1;
		}
		else
		{
			ptr = text;
			text = ft_strjoin(text, tmp);
			ft_strdel(&ptr);
			ft_strdel(&tmp);
		}
		ft_strdel(&heredoc);
	}
	ft_strdel(&heredoc);
	return (text);
}

static	int		ft_heredoc(t_redirection *redir, char *tty)
{
	char	*doc;
	int		fd;
	int		pip[2];

	doc = ft_document(redir);
	pipe(pip);
	ft_putstr_fd(doc, pip[1]);
	ft_strdel(&doc);
	close(pip[1]);
	fd = open (tty, O_RDWR);
	close(0);
	dup(fd);
	close(fd);
	dup2(pip[0], 0);
	close(pip[0]);
	return (255);
}

int				execute_redirection(t_redirection *redirection, char *tty)
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
		else if (current->type == AGGREGATION_IN)
		{
			if ((fd = ft_agg_in(current, fd)) < 0)
				break;
		}
		else if (redirection->type == HEREDOC)
			fd = ft_heredoc(current, tty);
		current = current->next;
	}
	return (fd);
}
