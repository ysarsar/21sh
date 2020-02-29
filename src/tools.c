/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:55:10 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/29 04:52:21 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		free_tab(char **arg)
{
	char 	**tab;
	int		i;

	tab = arg;
	i = -1;
	if (!tab)
		return ;
	while (arg[++i])
		ft_strdel(&arg[i]);
	free(arg);
}

void		exec_error(char *str, int c)
{
	if (c == 1)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": Permission denied.", 2);
	}
	else if (c == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": Command not found.", 2);
	}
}

void		error_msg(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": command not found.", 2);
}

int			args_len(char **args)
{
	int		i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int		ft_datalen(char *data)
{
	int	i;

	i = 0;
	while (data[i] != '\0')
	{
		if (data[i] == '=')
			break ;
		i++;
	}
	return (i);
}

int		print_error(int c)
{
	if (c == 1)
		ft_putendl_fd("setenv: Variable name must begin with a letter.", 2);
	else if (c == 2)
		ft_putendl_fd("setenv: too many arguments.", 2);
	return (1);
}

int		check_fd(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
	{
		if (str[i + 1] == '-')
			break;
		i++;
	}
	if (str[i] == '\0' || str[i] == '-')
		return (1);
	else if (str[i + 1] == '-' && str[i + 2] == '\0')
		return (1);
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": ambiguous redirect", 2);
	return (0);
}

int		check_word_fd(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			break;
		i++;
	}
	if (ft_isalpha(str[i]))
		return (0);
	return (1);
}

int		redirect_error(t_redirection *redirect)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(redirect->right, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (-1);
}

int		ft_argslen(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
