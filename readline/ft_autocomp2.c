/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autocomp2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:42:12 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/07 00:19:22 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_readline.h"

void					ft_alloc(t_auto **comp)
{
	*comp = (t_auto *)malloc(sizeof(t_auto));
	(*comp)->next = NULL;
	(*comp)->data = NULL;
}

char					**ft_splite_path(void)
{
	char				**envpath;
	int					i;
	char				*ptr;

	i = 0;
	if (!(envpath = ft_strsplit(getenv("PATH"), ':')))
		return (NULL);
	while (envpath[i])
	{
		ptr = envpath[i];
		envpath[i] = ft_strjoin(ptr, "/");
		ft_strdel(&ptr);
		i++;
	}
	return (envpath);
}

void					ft_if_is_dir(char **cm)
{
	struct stat			data;
	char				*ptr;

	lstat(*cm, &data);
	if (S_ISDIR(data.st_mode))
	{
		ptr = *cm;
		*cm = ft_strjoin(*cm, "/");
		ft_strdel(&ptr);
	}
}

void					ft_autoco(char **cmd, t_auto *comp)
{
	char				*cm;
	char				*clearrest;
	char				*ptr;

	if ((cm = ft_strrchr(*cmd, ' ')) == NULL)
	{
		ptr = *cmd;
		*cmd = ft_strdup(comp->data);
		ft_strdel(&ptr);
	}
	else
	{
		ptr = ft_clean_path(*cmd);
		cm = ft_strjoin(ptr, comp->data);
		ft_strdel(&ptr);
		if ((clearrest = ft_strrchr(*cmd, ' ') - 1))
			ft_strclr(&clearrest[1]);
		ft_if_is_dir(&cm);
		ptr = *cmd;
		*cmd = ft_strjoin(*cmd, cm);
		ft_strdel(&ptr);
		ft_strdel(&cm);
	}
}

void					comp(char **cmd)
{
	char				**path;
	t_auto				*comp;
	t_auto				*ptr;
	int					i;

	i = 0;
	ptr = NULL;
	if (!(path = ft_splite_path()))
		return ;
	if (ft_strchr(*cmd, ' '))
		comp = ft_search_in_dir(*cmd, ptr);
	else
		comp = ft_searchinpath(*cmd, path);
	ptr = comp;
	while (ptr && ptr->next)
	{
		ptr = ptr->next;
		i++;
	}
	if (i > 1 && !tputs(tgetstr("cd", NULL), 0, ft_putsfd))
		ft_print_argss(comp);
	if (i == 1)
		ft_autoco(cmd, comp);
	ft_free_tab(path);
	ft_free_lst(&comp);
}
