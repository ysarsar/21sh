/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 00:23:35 by ommadhi           #+#    #+#             */
/*   Updated: 2020/03/07 00:24:50 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_READLINE_H
# define FT_READLINE_H

# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <dirent.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <term.h>
# include <termios.h>
# include <stdio.h>
# include "../libft/libft.h"

# define SELECT 5263131
# define NOSELECT 5328667
# define CTRL_X 24
# define CTRL_W 23
# define CTRL_E 5
# define A_UP 1096489755
# define A_DOWN 1113266971
# define A_RIGHT 1130044187
# define A_LEFT 1146821403
# define HOME 4741915
# define END 4610843
# define ENTR 10
# define ESC 27
# define DEL2 2117294875
# define DEL 127
# define RIGHT 4414235
# define LEFT 4479771
# define UP 4283163
# define DOWN 4348699

# define B_SIZE 4096

int						g_last_his;
char					*g_cmd;
int						g_sig;
int						g_first;

struct					s_line
{
	char				*str;
	int					i;
}						g_l;

typedef struct			s_auto
{
	char				*data;
	struct s_auto		*next;
}						t_auto;

struct					s_copy
{
	int					from;
	int					to;
	char				*copy;
}						g_copy;

struct					s_pos
{
	int					x;
	int					y;
}						g_pos;

typedef	struct			s_xy
{
	int					x;
	int					y;
}						t_xy;

typedef struct			s_nod
{
	char				*data;
	char				*value;
	struct s_nod		*next;
}						t_nod;

typedef struct			s_his
{
	char				*data;
	struct s_his		*next;
	struct s_his		*prev;
}						t_his;

void					ft_alloc(t_auto **comp);
t_auto					*ft_search_in_dir(char *str, t_auto *head);
t_auto					*ft_searchinpath(char *str, char **envpath);
char					*ft_clean_path(char *str);
void					ft_print_argss(t_auto *comp);
void					ft_free_lst(t_auto **n);
void					sig_c(int sig);
void					ft_free_his(t_his **his);
void					ft_scroll(char *str, char *prp);
void					ft_cursor_motion(int *i, char *buff,
char **str, char *prp);
void					ft_alt_down_multi(int *i, char *str, int r, int prp);
void					ft_alt_up_multi(int *i, char *str, int r, int prp);
t_xy					ft_get_multi(int i, int prplen, char *str);
int						ft_printoperation(int r);
void					comp(char **cmd);
void					ft_free_his(t_his **his);
void					ft_copy_cut(char *cmd, int r);
void					ft_paste(char **cmd, int r, int *i);
void					ft_alt_down(int *i, char *str, int prp, int r);
void					ft_alt_up(int *i, char *str, int prplen, int r);
void					ft_save_cmd(int r, char *cmd);
void					get_cur_position(void);
void					ft_befor_return(char **str, int line,
int prplen, int read);
size_t					ft_del_char(char *str, int *i, int r);
int						ft_press_key(int *i, char *buff,
char **str, t_his **last);
t_xy					ft_get_col_line(int i, int prplen, char *str);
void					ft_goto(int i, int j);
char					*ft_read_quote(char *str);
void					ft_clear_line(char *str, int i);
void					ft_home_end_line(char *str, int *i, int r);
char					*ft_autocomp(char *str, t_his *his);
void					ft_new_his(t_his **ht);
t_his					*ft_add_his(t_his **ht, char *cmd);
char					*my_readline(t_his **history, char *prp);
void					ft_charjoin(char **s, char *buff, int *i);
void					ft_end_cur(char *str);
void					ft_go_up_down(int i, char **str, t_his **last);
void					ft_reset_cursor(int *index);
void					ft_mv_cusror(int r, int *i, char *str);
void					ft_alt_left_right(char *str, int *i, int r);
int						ft_dquote(char *cmd);

#endif
