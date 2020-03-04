/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 18:31:42 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/04 03:24:04 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char	*ft_var_name(char *str)
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

char	*ft_search_env(char *str, t_env *envp)
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

char	*ft_change_arg(char *key, char *str, char *var)
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

void	change_home(t_env **envp, char **arg)
{
	char	*key;
	char	*tmp;

	key = ft_search_env("HOME", *envp);
	tmp = ft_strdup(*arg + 1);
	if (ft_isalpha(tmp[0]))
	{
		ft_is_a_user(arg, key);
		ft_strdel(&tmp);
	}
	else
	{
		free(*arg);
		*arg = ft_strjoin(key, tmp);
		ft_strdel(&tmp);
	}
}

char	**line_error(char *str)
{
	ft_putstr(str);
	ft_putendl(": Undefined variable.");
	ft_strdel(&str);
	return (NULL);
}
