/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 21:58:57 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/04 04:31:03 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int			ft_env(t_env *envp)
{
	t_env *current;

	current = envp;
	while (current)
	{
		ft_putendl(current->data);
		current = current->next;
	}
	return (1);
}

int			ft_setenv(t_env **envp, char **args)
{
	int		i;

	i = ft_argslen(args);
	if (i == 1)
		ft_env(*envp);
	else if (i == 2)
	{
		if (!ft_isalpha(args[1][0]))
			return (print_error(1));
		ft_add_variable(envp, args, 2);
	}
	else if (i == 3)
	{
		if (!ft_isalpha(args[1][0]))
			return (print_error(1));
		ft_add_variable(envp, args, 3);
	}
	else
		return (print_error(2));
	return (1);
}

int			ft_unsetenv(t_env **envp, char **args)
{
	int		i;
	char	*var;

	i = ft_argslen(args);
	if (i > 1)
	{
		i = 0;
		while (args[++i])
		{
			var = ft_strcat(args[i], "=");
			delete_var(envp, var);
		}
	}
	else
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
	return (1);
}

int			ft_cd(char **args, t_env *envp)
{
	int		i;
	char	*home;
	char	*var;
	char	*cwd;
	char	buff[PATH_MAX + 1];

	i = ft_argslen(args);
	var = NULL;
	cwd = getcwd(buff, PATH_MAX + 1);
	if ((home = getenv("HOME")))
	{
		ft_cd_glob(home, args, envp, var);
		ft_env_owd(cwd, envp);
		ft_env_cwd(envp);
	}
	else
		ft_putendl_fd("21sh: cd: HOME not set", 2);
	return (1);
}

int			ft_echo(char **args)
{
	int		i;

	i = 1;
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1] != NULL)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
	return (1);
}
