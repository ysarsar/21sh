/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:13:27 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/22 00:29:47 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	void	execute_without_path(char **args, char **tab)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (access(args[0], F_OK) == 0)
		{
			if (access(args[0], X_OK) == 0)
			{
				if (execve(args[0], args, tab) == -1)
					ft_putendl("21sh: Error exec.");
			}
			else
				exec_error(args[0], 1);
		}
		else
			exec_error(args[0], 2);
		exit(1);
	}
	else if (pid < 0)
		ft_putendl("21sh: Error forking.");
	else
		wait(NULL);
}

static	void	sh_lunche(char *cmd_name, char **args, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_name, args, env) == -1)
			ft_putendl("21sh: error exec");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		ft_putendl("21sh: error forking");
	else
		wait(NULL);
}

static	void	execute_with_path(char **args, char **tab)
{
	char	*path;

	path = valid_path(args[0], tab);
	if (!path)
	{
		exec_error(args[0], 2);
		return ;
	}
	else if (access(path, X_OK) == 0)
		sh_lunche(path, args, tab);
	else
		exec_error(args[0], 1);
	
	ft_strdel(&path);
}

int				execute_simple_cmd(char *cmd, char **tab, t_env **envp)
{
	char		**args;
	int			i;

	args = ft_strsplit(cmd, -1);
	// if ((i = check_builtins(args, envp)))
	// {
	// 	if (i == 2)
	// 	{
	// 		free_tab(args);
	// 		return (0);
	// 	}
	// }
	/*else */if (args[0][0] == '/' || args[0][0] == '.')
		execute_without_path(args, tab);
	else
		execute_with_path(args, tab);
	free_tab(args);
	return (1);
}