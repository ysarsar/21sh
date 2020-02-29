/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:16:08 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/29 01:07:42 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int			execute_pipe(t_parse *ast, t_env **envp, char **tab, char *tty)
{
	int		pip[2];
	int		pid;
	int		cmd_nbr;
	int		tmp, fd;
	t_parse	*current;

	current = ast;
	cmd_nbr = 0;
	tmp = 0;
	while (current)
	{
		if (pipe(pip) == -1)
			return (-1);
		pid = fork();
		if (pid == 0)
		{
			close(pip[0]);
			if (cmd_nbr != 0 && fd != 255)
				dup2(tmp, 0);
			if (current->pipe)
				dup2(pip[1], 1);
			if (current->redirection)
			{
				if (current->redirection->type == HEREDOC)
					ft_reset_fd(tty, fd);
				execute_redirection(current->redirection, tty);
			}
			close(pip[1]);
			execute_simple_cmd(current->cmd, tab, envp);
			exit(0);
		}
		close(pip[1]);
		if (cmd_nbr != 0)
			close(tmp);
		tmp = pip[0];
		cmd_nbr++;
		current = current->pipe;
	}
	close(tmp);
	if (pid)
		while (wait(NULL) > 0)
		{
		}
	return (255);
}
