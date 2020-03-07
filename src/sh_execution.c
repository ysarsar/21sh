/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:29:12 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/04 01:54:40 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	char	**list_to_tabs(t_env **envp)
{
	t_env	*current;
	char	**tabs;
	int		i;

	current = *envp;
	tabs = NULL;
	i = -1;
	if (!current)
		return (NULL);
	while (++i >= 0 && current != NULL)
		current = current->next;
	if (!(tabs = (char **)ft_memalloc(sizeof(char*) * (i + 1))))
		return (tabs);
	i = 0;
	current = *envp;
	while (current != NULL)
	{
		if (current->data)
			tabs[i] = ft_strdup(current->data);
		current = current->next;
		i++;
	}
	tabs[i] = NULL;
	return (tabs);
}

void			ft_reset_fd(char *tty, int file_d)
{
	int		fd;

	fd = open(tty, O_RDWR);
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	if (file_d > 2)
		close(file_d);
	if (fd > 2)
		close(fd);
}

int				sh_execute(t_parse **ast, t_env **envp, char *tty)
{
	t_parse *current;
	char	**tabs;
	int		status;
	int		fd;

	current = *ast;
	status = 1;
	fd = 0;
	tabs = list_to_tabs(envp);
	while (current)
	{
		if (current->pipe)
			fd = execute_pipe(current, envp, tabs, tty);
		else
		{
			if (current->redirection)
				fd = execute_redirection(current->redirection, tty);
			if (fd >= 0)
				status = execute_simple_cmd(current->cmd, tabs, envp);
			ft_reset_fd(tty, fd);
		}
		current = current->sep;
	}
	free_tabs(tabs);
	return (status);
}
