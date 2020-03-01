/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 16:55:10 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/01 06:06:23 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		exec_error(char *str, int c)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(str, 2);
	if (c == 1)
		ft_putendl_fd(": Permission denied.", 2);
	else if (c == 2)
		ft_putendl_fd(": Command not found.", 2);
}

int			ft_datalen(char *data)
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

int			print_error(int c)
{
	if (c == 1)
		ft_putendl_fd("setenv: Variable name must begin with a letter.", 2);
	else if (c == 2)
		ft_putendl_fd("setenv: too many arguments.", 2);
	return (1);
}

int			redirect_error(t_redirection *redirect)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(redirect->right, 2);
	ft_putendl_fd(": No such file or directory", 2);
	return (-1);
}

int			ft_argslen(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
