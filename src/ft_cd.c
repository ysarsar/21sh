/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 02:20:55 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/29 08:07:52 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	char	*ft_changedir(char *str, char *cwd)
{
	char	*var;
	char	*path;

	var = ft_strjoin(cwd, "/");
	path = ft_strjoin(var, str);
	ft_strdel(&var);
	return (path);
}

static	char	*ft_search_env(char *str, t_env *envp)
{
	t_env *current;

	current = envp;
	while (current)
	{
		if (ft_strncmp(current->data, str, ft_strlen(str)) == 0)
			return (&(current->data[ft_datalen(current->data) + 1]));
		current = current->next;
	}
	return (NULL);
}

static	int		ft_cd_back(char *cwd, t_env *envp)
{
	char	*var;

	if (!(var = ft_search_env("OLDPWD", envp)))
		var = cwd;
	ft_putendl_fd(var, 2);
	if (chdir(var) < 0)
		ft_putendl_fd("21sh: cd: No such file or directory", 2);
	// ft_env_owd(cwd, envp);
	// ft_env_cwd(envp);
	return (1);
}

static	int		ft_cd_dir(char *cwd, t_env *envp, char **args)
{
	if (chdir(args[1]) < 0)
	{
		ft_putstr_fd("21sh: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	// ft_env_owd(cwd, envp);
	// ft_env_cwd(envp);
	return (1);
}

static	void	ft_cd_int(char *var, char **args, char *cwd)
{
	var = ft_changedir(args[1], cwd);
	if (access(var, F_OK) == 0)
	{
		if (access(var, X_OK) == 0)
			chdir(var);
		else
		{
			ft_putstr_fd("21sh: cd: permission denied: ", 2);
			ft_putendl_fd(args[1], 2);
		}
	}
	else
	{
		ft_putstr_fd("21sh: cd: no such file or directory: ", 2);
		ft_putendl_fd(args[1], 2);
	}
	ft_strdel(&var);
}

int				ft_cd_glob(char *home, char **args, t_env *envp, char *var)
{
	char	*cwd;
	char	buff[PATH_MAX + 1];
	int		i;

	cwd = getcwd(buff, PATH_MAX + 1);
	i = ft_argslen(args);
	if (i == 1)
		chdir(home);
	else if (i == 2)
	{
		if (ft_strcmp(args[1], "-") == 0)
			return (ft_cd_back(cwd, envp));
		else
		{
			if (args[1][0] == '/')
				return (ft_cd_dir(cwd, envp, args));
			else
			{
				if (cwd)
					ft_cd_int(var, args, cwd);
			}
		}
	}
	return (1);
}