/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 22:29:09 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/29 08:15:30 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			list_push(char *var, t_env **envp)
{
	t_env *current;
	t_env *new_node;

	current = *envp;
	if (!(new_node = (t_env*)ft_memalloc(sizeof(t_env))))
		exit(EXIT_FAILURE);
	new_node->data = ft_strdup(var);
	new_node->next = NULL;
	if (!current)
	{
		*envp = new_node;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void			ft_add_variable(t_env **envp, char **args, int c)
{
	t_env	*env;
	char	*var;

	env = *envp;
	var = ft_strcat(args[1], "=");
	if (c == 3)
		var = ft_strcat(var, args[2]);
	while (env)
	{
		if (ft_strncmp(env->data, args[1], ft_datalen(env->data)) == 0)
		{
			ft_strdel(&env->data);
			env->data = ft_strdup(var);
			break ;
		}
		env = env->next;
	}
	if (!env)
		list_push(var, envp);
}

int				delete_var(t_env **env, char *arg)
{
	t_env	*temp;
	t_env	*prev;
	t_env	*envp;

	envp = *env;
	temp = *env;
	if (temp != NULL && (ft_strncmp(temp->data, arg, ft_strlen(arg)) == 0))
	{
		*env = temp->next;
		ft_strdel(&temp->data);
		free(temp);
		return (1);
	}
	while (temp != NULL && (ft_strncmp(temp->data, arg, ft_strlen(arg)) != 0))
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return (0);
	prev->next = temp->next;
	ft_strdel(&temp->data);
	free(temp);
	return (1);
}
