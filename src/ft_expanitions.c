/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expanitions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 04:48:47 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/04 04:54:27 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static int		search_slash(char *str)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '/')
			break ;
		i++;
	}
	return (i);
}

int				ft_is_a_user(char **str, char *key)
{
	int		ch;
	char	*user;
	char	*ptr;
	char	*tmp;

	ptr = *str;
	tmp = NULL;
	ch = search_slash(key);
	user = ft_strndup(key, ch + 1);
	tmp = ft_strjoin(user, *str + 1);
	if (!access(tmp, F_OK))
	{
		free(*str);
		*str = tmp;
		ft_strdel(&user);
		return (1);
	}
	ft_strdel(&tmp);
	ft_strdel(&user);
	return (0);
}

char			**ft_expantions(char **args, t_env **envp)
{
	int		i;
	char	*var;
	char	*key;
	char	*tmp;

	i = -1;
	while (args[++i])
	{
		if (args[i][0] == '~')
			change_home(envp, &args[i]);
		if (ft_is_there(args[i], '$'))
		{
			if ((var = ft_var_name(args[i])) == NULL)
				break ;
			key = ft_search_env(var, *envp);
			if (key == NULL)
				return (line_error(var));
			tmp = ft_change_arg(key, args[i], var);
			ft_strdel(&args[i]);
			args[i] = ft_strdup(tmp);
			ft_strdel(&tmp);
			ft_strdel(&var);
		}
	}
	return (args);
}
