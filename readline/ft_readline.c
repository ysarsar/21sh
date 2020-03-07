/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 14:48:56 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/05 01:58:43 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void					ft_myputs(char *str, int from, int to, char *prp)
{
	int					i;
	struct winsize		w;

	i = 0;
	ioctl(1, TIOCGWINSZ, &w);
	ft_goto(g_pos.x - 1, g_pos.y - 1);
	tputs(tgetstr("cr", NULL), 0, ft_putsfd);
	tputs(tgetstr("cd", NULL), 0, ft_putsfd);
	ft_putstr(prp);
	while (str[i])
	{
		if (i <= to && i >= from)
			ft_putc2str("\033[7m", str[i], "\033[0m");
		else if (i >= to && i <= from)
			ft_putc2str("\033[7m", str[i], "\033[0m");
		else
			ft_putchar(str[i]);
		i++;
	}
}

int						ft_scroll_and_print(char *str, char *prp)
{
	ft_scroll(str, prp);
	ft_myputs(str, g_copy.from, g_copy.to, prp);
	return (0);
}

char					*ft_readline(t_his **ht, char *prp)
{
	char				buff[4096];
	t_xy				xy;
	int					check;

	g_line.i = 0;
	g_line.str = ft_strnew(0);
	while (prp[0] != '>' && *ht && (*ht)->next)
		(*ht) = (*ht)->next;
	(*(int*)buff) = 0;
	while (!ft_strclr(buff) && (check = read(0, buff, 4096)) > 0)
	{
		buff[check] = '\0';
		check = g_line.i;
		ft_cursor_motion(&g_line.i, buff, &g_line.str, prp);
		if (ft_press_key(&g_line.i, buff, &g_line.str, ht) || (g_line.str[0] == '\0' && (*(int*)buff) == 4))
			break ;
		(buff[0] != 9 || check != g_line.i) ? ft_scroll_and_print(g_line.str, prp) : 0;
		(ft_strchr(g_line.str, '\n')) ? (xy = ft_get_multi(g_line.i, ft_strlen(prp), g_line.str))
			: (xy = ft_get_col_line(g_line.i, ft_strlen(prp), g_line.str));
		ft_goto(xy.x, g_pos.y + xy.y - 1);
	}
	ft_befor_return(&g_line.str, g_pos.y, ft_strlen(prp), (*(int*)buff));
	return (g_line.str);
}

char					*my_readline(t_his **history, char *prp)
{
	struct termios		config;
	int					fd;

	g_last_his = 0;
	g_first = 0;
	g_copy.from = -1;
	g_copy.to = -1;
	g_sig = 0;

	signal(SIGINT, sig_c);
	if ((fd = open("/dev/tty", O_RDWR)) < 0)
	{
		ft_putstr("21sh: Canot Open fd !!\n");
		return (NULL);
	}
	if (tcgetattr(fd, &config) < 0)
		return (NULL);
	config.c_lflag &= ~(ECHO | ICANON);
	if (tcsetattr(fd, TCSANOW, &config) < 0)
		return (NULL);
	if (!tgetent(NULL, getenv("TERM")) || !getenv("TERM"))
	{
		ft_putendl_fd("failure to unitialise Temrcap", 2);
		return (NULL);
	}
	get_cur_position();
	if (!g_sig)
	{
		tputs(tgetstr("cr", NULL), 0, ft_putsfd);
	    tputs(tgetstr("cd", NULL), 0, ft_putsfd);
		ft_putstr(prp);
	}
	else
		ft_putstr(prp);
	return (ft_readline(history, prp));
}
