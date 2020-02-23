/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 21:58:57 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/22 23:48:09 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		ft_env(t_env *envp)
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

int		ft_setenv(t_env **envp, char **args)
{
	int		i;

	i = args_len(args);
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
	int 	i;
	char	*var;

	i = args_len(args);
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