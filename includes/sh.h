/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 22:55:49 by ysarsar           #+#    #+#             */
/*   Updated: 2020/03/11 08:13:36 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

# include "../libft/libft.h"
# include <stdio.h>
# include <limits.h>
# include "ft_readline.h"

# define TABLE_SIZE 1000

typedef	struct				s_ht
{
	char					*value;
	char					*key;
	int						hits;
	struct	s_ht			*next;
}							t_ht;

typedef	struct				s_hash
{
	t_ht					**list;
}							t_hash;

typedef struct				s_env
{
	char					*data;
	struct s_env			*next;
}							t_env;

typedef	struct				s_pipe_variable
{
	int						pip[2];
	int						cmd_nbr;
	int						tmp;
	int						pid;
	char					*tty;
}							t_pipe_variable;

typedef	struct				s_quote_var
{
	int						j;
	char					c;
}							t_quote_var;

typedef	struct				s_token_v
{
	int						k;
	char					*str;
}							t_token_v;

typedef	enum				e_type
{
	WORD,
	SEPARATEUR,
	PIPE,
	R_FD,
	L_FD,
	REDIR_IN,
	REDIR_OUT,
	APPEND_OUT,
	AGGREGATION_OUT,
	AGGREGATION_IN,
	HEREDOC
}							t_type;

typedef	struct				s_redirection
{
	char					*left;
	char					*right;
	t_type					type;
	struct s_redirection	*next;
}							t_redirection;

typedef	struct				s_token
{
	char					*value;
	t_type					type;
}							t_token;

typedef struct				s_parse
{
	char					*cmd;
	t_redirection			*redirection;
	struct s_parse			*pipe;
	struct s_parse			*sep;
}							t_parse;

void						sh_loop(t_env **envp);

void						free_ast(t_parse **ast);

int							ft_next_token(char **line, t_token **tok,
										int mode, t_his **his);

int							ft_separators(t_token **tok, char *str, int i);
int							ft_redirection(char *str,
											t_token **tok, int i, int *redir);
int							ft_is_numeric(char *str);
int							ft_check_fd(t_token_v v,
										char **tmp, t_token **token, int mode);
int							ft_check_word(t_token **token, char **tmp);
int							ft_quotes(char **cmd,
										int i, char **tmp_token, t_his **his);

t_parse						*ft_parse_tree(char **line, t_his **his);

void						ft_word_type(t_parse **ast, t_token **token);
int							ft_separateur_type(t_parse **ast,
											t_parse *current, t_token *token);
int							ft_pipe_type(t_parse **ast, t_token *token);
int							ft_redirection_type(t_parse **ast, t_token *token);

int							check_syntax(t_parse *ast);

int							sh_execute(t_parse **ast, t_env **envp, char *tty, t_hash **h_table);

int							execute_simple_cmd(char *cmd,
											char **tabs, t_env **envp, t_hash **h_table);
char						*valid_path(char *cmd_name, char **tabs);

int							ft_env(t_env *envp);
int							ft_setenv(t_env **envp, char **args);
int							ft_unsetenv(t_env **envp, char **args);
int							ft_cd(char **args, t_env *envp);
int							ft_echo(char **args);

int							ft_cd_glob(char *home, char **args,
										t_env *envp, char *var);
void						ft_env_cwd(t_env *envp);
void						ft_env_owd(char *cwd, t_env *envp);
int							ft_cd_glob(char *home, char **args,
										t_env *envp, char *var);

void						ft_add_variable(t_env **envp, char **args, int c);
int							delete_var(t_env **env, char *arg);
void						list_push(char *var, t_env **envp);

int							execute_redirection(t_redirection
											*redirection, char *tty);
void						ft_reset_fd(char *tty, int file_d);
int							ft_redir_inout(t_redirection *redirect, int fd);
int							ft_redir_append(t_redirection *redir, int fd);
int							ft_agg_digit(t_redirection *redir,
										int fd, int left);
int							ft_agg_close(t_redirection *redir,
										int fd, int left);
int							ft_agg_word(t_redirection *redir, int fd, int left);
char						*ft_document(char *redir_right);

int							execute_pipe(t_parse *ast, t_env **envp,
										char **tabs, char *tty, t_hash **h_table);

char						**ft_expantions(char **args, t_env **envp);

char						*ft_var_name(char *str);
char						*ft_search_env(char *str, t_env *envp);
char						*ft_change_arg(char *key, char *str, char *var);
void						change_home(t_env **envp, char **arg);
char						**line_error(char *str);
int							ft_is_a_user(char **str, char *key);

char						*free_tabs(char **arg);
void						exec_error(char *str, int c);
int							ft_argslen(char **args);
int							ft_datalen(char *data);
int							print_error(int c);
int							redirect_error(t_redirection *redirect);
void						listpush(char *var, t_env **envp);
void						free_str(char *ptr, char *tmp);
char						*ft_changedir(char *str, char *cwd);
int							is_white(char c);
int							free_tabs2(char **args, char **arr);
int							is_special(char c);

// hash function
t_hash			*ht_create(void);
char			*ft_hashtable(char **args, char **tabs, t_hash **h_table);
void			ft_hash(char **args, t_hash **h_table);

#endif
