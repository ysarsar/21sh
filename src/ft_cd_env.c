/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 04:33:50 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/04 04:33:28 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	ft_env_owd(char *cwd, t_env *envp)
{
	t_env	*current;
	char	*var;

	current = envp;
	while (current)
	{
		if (ft_strncmp("OLDPWD=", current->data, ft_strlen("OLDPWD=")) == 0)
			break ;
		current = current->next;
	}
	if (current)
	{
		var = ft_strjoin("OLDPWD=", cwd);
		if (var)
		{
			free(current->data);
			current->data = var;
		}
	}
	else
		list_push("OLDPWD=", &envp);
}

void	ft_env_cwd(t_env *envp)
{
	t_env	*current;
	char	buff[PATH_MAX + 1];
	char	*cwd;

	current = envp;
	while (current)
	{
		if (ft_strncmp("PWD=", current->data, ft_strlen("PWD=")) == 0)
			break ;
		current = current->next;
	}
	cwd = getcwd(buff, PATH_MAX + 1);
	if (current)
	{
		if (cwd)
		{
			free(current->data);
			current->data = ft_strjoin("PWD=", cwd);
		}
	}
	else
		list_push("PWD=", &envp);
}
