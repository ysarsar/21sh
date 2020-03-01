/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 18:31:42 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/01 14:43:55 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static	int		is_special(char c)
{
	if (c == '#' || c == '/' || c == '~' || c == '@'
		|| c == '^' || c == '$')
		return (1);
	return (0);
}

static	char	*ft_var_name(char *str)
{
	int		i;
	int		j;
	char	tmp[1024];
	char	*var;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '$')
		i++;
	i++;
	if (str[i] == '\0' || str[i] == '$')
		return (NULL);
	while (str[i])
	{
		if (is_special(str[i]))
			break ;
		tmp[j] = str[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	var = ft_strdup(tmp);
	return (var);
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

static	char	*ft_change_arg(char *key, char *str, char *var)
{
	int		i;
	int		j;
	int		k;
	char	tmp[1024];

	i = -1;
	j = -1;
	while (str[++i] != '$')
		tmp[i] = str[i];
	k = i;
	while (key[++j])
	{
		tmp[i] = key[j];
		i++;
	}
	j = k + ft_strlen(var) + 1;
	while (str[j])
	{
		tmp[i] = str[j];
		j++;
		i++;
	}
	tmp[i] = '\0';
	return (ft_strdup(tmp));
}

static	void	change_home(t_env **envp, char **arg)
{
	char	*key;
	char	*tmp;

	key = ft_search_env("HOME", *envp);
	tmp = ft_strdup(*arg + 1);
	free(*arg);
	*arg = ft_strjoin(key, tmp);
	ft_strdel(&tmp);
}

static	char	**line_error(char *str)
{
	ft_putstr(str);
	ft_putendl(": Undefined variable.");
	ft_strdel(&str);
	return (NULL);
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
		if (args[i][0] == '~' && !(ft_isalpha(args[i][1])))
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
