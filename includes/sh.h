/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysarsar <ysarsar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 22:55:49 by ysarsar           #+#    #+#             */
/*   Updated: 2020/02/26 22:32:14 by ysarsar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SH_H
# define SH_H

# include "../libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>


// Linked list for storing environement
typedef struct				s_env
{
	char					*data;
	struct s_env			*next;
}							t_env;

// Token types
typedef enum				s_type
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

// Linked list for redirections
typedef	struct				s_redirection
{
	char					*left;
	char					*right;
	struct	s_redirection	*next;
	t_type					type;
}							t_redirection;

// Struct for tokens
typedef	struct				s_token
{
	char					*value;
	t_type					type;
}							t_token;

// Parse tree
typedef	struct 				s_parse
{
	char					*cmd;
	t_redirection			*redirection;
	struct	s_parse			*pipe;
	struct	s_parse			*sep;
}							t_parse;

// shell functions
void						sh_loop(t_env **envp);

void						free_ast(t_parse **ast);

// tokenz functions
int							ft_next_token(char **line, t_token **tok,int mode);

int							ft_separators(t_token **tok, char *str, int i);
int							is_white(char c);
int							ft_redirection(char *str, t_token **tok, int i, int *redir);
int							ft_is_numeric(char *str);
int							ft_check_fd(char *str, char **tmp, t_token **token, int i, int mode);
int							ft_check_word(t_token **token, char **tmp);
int							ft_quotes(char **cmd, int i, char **tmp_token);

// parse functions
t_parse						*ft_parse_tree(char **line);

void						ft_word_type(t_parse **ast, t_token **token);
int							ft_separateur_type(t_parse **ast, t_parse *current, t_token *token);
int							ft_pipe_type(t_parse **ast,t_token *token);
int							ft_redirection_type(t_parse **ast, t_token *token);

// Check syntax function
int							check_syntax(t_parse *ast);

// Execution functions
int         				sh_execute(t_parse **ast, t_env **envp, char *tty);

int							execute_simple_cmd(char *cmd, char **tab, t_env **envp);
char						*valid_path(char *cmd_name, char **tab);

// Builtins functions
int							ft_env(t_env *envp);
int							ft_setenv(t_env **envp, char **args);
int							ft_unsetenv(t_env **envp, char **args);

// Environement func
void						ft_add_variable(t_env **envp, char **args, int c);
int							delete_var(t_env **env, char *arg);

// Redirection functions
int							execute_redirection(t_redirection *redirection);

// Tools function
void						free_tab(char **arg);
void						exec_error(char *str, int c);
void						error_msg(char *str);
int							args_len(char **args);
int							ft_datalen(char *data);
int							print_error(int c);
int							check_fd(char *str);
int							check_word_fd(char *str);
int							check_fd(char *str);

#endif