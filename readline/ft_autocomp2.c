/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_autocomp2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 00:42:12 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/04 04:27:37 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void					ft_free_lst(t_auto **n)
{
	t_auto				*nd;
	t_auto				*tmp;

	nd = *n;
	while (nd)
	{
		tmp = nd->next;
		ft_strdel(&nd->data);
		free(nd);
		nd = tmp;
	}
}

void					ft_print_colors(char *name)
{
	struct stat			type;

	lstat(name, &type);
	if (S_ISLNK(type.st_mode))
		ft_put4str(NULL, "\033[1;35m", name, "\033[0m");
	else if (S_ISDIR(type.st_mode))
		ft_put4str(NULL, "\033[1;36m", name, "\033[0m");
	else if (!S_ISDIR(type.st_mode) && type.st_mode & S_IXOTH)
		ft_put4str(NULL, "\033[1;31m", name, "\033[0m");
	else
		ft_putstr(name);
}

int						ft_max_lent(t_auto *comp)
{
	int					i;
	int					lent;

	i = 0;
	while (comp && comp->next)
	{
		if (i < (lent = ft_strlen(comp->data)))
			i = lent;
		comp = comp->next;
	}
	return (i);
}

void					ft_print_argss(t_auto *comp)
{
	int					maxlent;
	struct winsize		w;
	int					i;
	int					j;

	ioctl(1, TIOCGWINSZ, &w);
	i = 0;
	j = g_pos.y;
	maxlent = ft_max_lent(comp);
	while (comp && comp->next && j < w.ws_row)
	{
		if ((i + maxlent) > w.ws_col)
		{
			i = 0;
			j++;
		}
		tputs(tgoto(tgetstr("cm", NULL), i, j), 0, ft_putsfd);
		ft_print_colors(comp->data);
		i = i + maxlent + 1;
		comp = comp->next;
	}
	tputs(tgoto(tgetstr("cm", NULL), i, j + 1), 0, ft_putsfd);
}

void					ft_alloc(t_auto **comp)
{
	*comp = (t_auto *)malloc(sizeof(t_auto));
	(*comp)->next = NULL;
	(*comp)->data = NULL;
}

char					*ft_clean_path(char *str)
{
	int					i;
	int					j;

	j = ft_strlen(str);
	i = ft_strlen(str);
	if (!(ft_strrchr(str, '/')))
		return (ft_strnew(0));
	while (str[j] != ' ' && j > 0)
		j--;
	if (str[j] == ' ')
		j++;
	while (i > 0 && str[i] != '/')
		i--;
	i++;
	return (ft_strsub(str, j, i - j));
}

t_auto					*ft_search_in_dir(char *str)
{
	char				*path;
	char				*s;
	DIR					*dr;
	struct dirent		*dir;
	t_auto				*comp;
	t_auto				*head;

	if ((s = ft_strrchr(str, '/')) == NULL)
	{
		path = ft_strdup(".");
		s = ft_strrchr(str, ' ');
	}
	else
		path = ft_clean_path(str);
	ft_alloc(&comp);
	head = comp;
	if (!(dr = opendir(path)))
	{
		ft_strdel(&path);
		return (NULL);
	}
	while ((dir = readdir(dr)) != NULL)
	{
		if (((ft_strncmp(s, dir->d_name, ft_strlen(s)) == 0) || !s))
		{
			comp->data = ft_strdup(dir->d_name);
			ft_alloc(&comp->next);
			comp = comp->next;
		}
	}
	closedir(dr);
	ft_strdel(&path);
	return (head);
}

t_auto					*ft_searchinpath(char *str, char **envpath)
{
	DIR					*dr;
	struct dirent		*dir;
	int					i_l[2];
	t_auto				*comp;
	t_auto				*head;

	i_l[1] = ft_strlen(str);
	ft_alloc(&comp);
	head = comp;
	i_l[0] = -1;
	while (envpath[++i_l[0]])
	{
		if (!(dr = opendir(envpath[i_l[0]])))
			return (NULL);
		while ((dir = readdir(dr)) != NULL)
			if ((ft_strncmp(str, dir->d_name, i_l[1]) == 0 || str[0] == '\0'))
			{
				comp->data = ft_strdup(dir->d_name);
				ft_alloc(&comp->next);
				comp = comp->next;
			}
		closedir(dr);
	}
	return (head);
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

void					ft_autoco(char **cmd, t_auto *comp)
{
	struct stat			data;
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
		lstat(cm, &data);
		if (S_ISDIR(data.st_mode))
		{
			ptr = cm;
			cm = ft_strjoin(cm, "/");
			ft_strdel(&ptr);
		}
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
	if (!(path = ft_splite_path()))
		return ;
	if (ft_strchr(*cmd, ' '))
		comp = ft_search_in_dir(*cmd);
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
