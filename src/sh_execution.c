/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:29:12 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/23 19:02:33 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

static  char	**list_to_tab(t_env **envp)
{
	t_env	*current;
	char	**tab;
	int		i;

	current = *envp;
	tab = NULL;
	i = 0;
    if (!current)
		return (NULL);
	while (current != NULL)
	{
		current = current->next;
		i++;
	}
	if (!(tab = (char **)ft_memalloc(sizeof(char*) * (i + 1))))
		return (tab);
	i = 0;
	current = *envp;
	while (current != NULL)
	{
		if (current->data)
			tab[i] = ft_strdup(current->data);
		current = current->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int         sh_execute(t_parse **ast, t_env **envp)
{
    t_parse *current;
    char    **tab;
    int     status;
	int		fd[4];

    current = *ast;
    status = 1;
    tab = list_to_tab(envp); //must be freed here ^_^
    while (current)
    {
		fd[0] = dup(0);
		fd[1] = dup(1);
		fd[2] = dup(2);
        // if (current->pipe)
        //     execute_pipe(current, envp, tab);
        // else
        // {
            if (current->redirection)
                fd[3] = execute_redirection(current->redirection);
            status = execute_simple_cmd(current->cmd, tab, envp);
        // }
		close(fd[3]);
		close(0);
		dup(fd[0]);
		close(fd[0]);
		close(1);
		dup(fd[1]);
		close(fd[1]);
		close(2);
		dup(fd[2]);
		close(fd[2]);
        current = current->sep;
    }
    free_tab(tab);
    return (status);
}