/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:29:12 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/25 17:22:31 by ysarsar          ###   ########.fr       */
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
	int		fd[2];

    current = *ast;
    status = 1;
    tab = list_to_tab(envp); //must be freed here ^_^
    while (current)
    {
		fd[0] = fork();
		if (fd[0] == 0)
		{
        // if (current->pipe)
        //     execute_pipe(current, envp, tab);
        // else
        // {
            if (current->redirection)
                fd[1] = execute_redirection(current->redirection);
			if (fd[1] >= 0)
            	status = execute_simple_cmd(current->cmd, tab, envp);
			exit(0);
        // }
		}
		else
			wait(NULL);
        current = current->sep;
    }
    free_tab(tab);
    return (status);
}