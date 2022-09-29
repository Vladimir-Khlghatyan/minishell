/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhlghat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 14:32:04 by vkhlghat          #+#    #+#             */
/*   Updated: 2022/09/25 14:32:08 by vkhlghat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "defines.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <errno.h>
# include <sys/ioctl.h>

int	g_sigint_flag;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				print_flag;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_inputs
{
	char			**args;
	char			*type;
	int				quote_in_hd_limiter;
	int				redir_is_last;
	struct s_inputs	*prev;
	struct s_inputs	*next;
}				t_inputs;

typedef struct s_data
{
	int				single_builin;
	int				unexp_token;
	int				here_doc;
	int				fdin;
	int				fdout;
	int				exit_flag;
	int				here_doc_cnt;
	int				proc_cnt;
	int				pipefd_cnt;
	int				*pipefds;
	pid_t			pid;
	char			**path_arr;
	char			**env_arr;
	char			*cmd;
	t_env			*env;
	t_inputs		*inp;
}				t_data;

//==========================================================================
//	lexer
//==========================================================================

char		**lexer(char *str);
int			check_unclosed_quotes(char *str, int i, int q1, int q2);
int			double_quotes(char *str, int *i, int *cnt);
int			single_quotes(char *str, int *i, int *cnt);
int			metacharacters(char *str, int *i, int *cnt);
int			non_metacharacters(char *str, int *i, int *cnt);
char		**remove_empty_tokens(char **tokens, int i, int j, int cnt);
int			pipe_exist(char *str);

//==========================================================================
//	parser
//==========================================================================

t_inputs	*parser(t_env *env, char **tokens);
t_inputs	*lexer_parser(t_env *env, char *str);
void		t_inputs_print(t_inputs *inp);
void		t_inputs_fill_new_nod(t_inputs *new, char **toks, int *i, int len);
void		t_inputs_heredoc_limiter_del(t_inputs *inp);
void		t_inputs_del_node(t_inputs **head, t_inputs **node);
void		t_inputs_replace_unexp_node(t_inputs *inp);
void		t_inputs_tokens_sort(t_inputs *inp);
void		t_inputs_corrections(t_inputs *inp);
int			ft_strcnt(char *str);
int			*ft_intarr_for_split(char *str, int i, int cnt);
char		**ft_split_dollar(char *str, int i, int j);
char		**quotedstrtoarr(char *str);
char		*join_arr_to_str(char **arr);
char		*check_and_replace_str1(t_env *env, char *str);
char		*check_and_replace_str2(t_env *env, char *str, int split_flag);
char		*str_dollar_sign_handler(t_env *env, char *str);
void		t_inputs_dollar_sign_handler(t_env *env, t_inputs *inp);
void		t_inputs_builtin_types_set(t_inputs *inp);
void		t_inputs_hd_limiter_parse(t_inputs *inp);

//==========================================================================
//	minishell
//==========================================================================

void		display_prompt(t_env *env);
int			main(int ac, char **av, char **envp);

//==========================================================================
//	utils
//==========================================================================

int			ft_putstr_fd(char *str1, char *str2, char *str3, int fd);
int			error_message(t_env *env, char *err, char *str, int exit_status);
void		error_message_and_exit(char *str, int exit_status);
void		exit_message_on_ctrl_d(char *str, int exit_status);
void		ft_history(char *buffer);
int			ft_sign(char *str);
long long	ft_atoll(char *str);
char		*ft_lltoa(long long n);
char		**ft_arrfree(char **arr);
void		ft_envfree(t_env *env);
void		ft_inputsfree(t_inputs *inp);
void		t_env_free_node(t_env *node);
char		*ft_strchr(char *s, int c);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strdup(char *src);
char		*ft_strdup_for_builtin_cd(char *src);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strjoin_free(char *s1, char *s2);
int			ft_strlen(char *str);
int			ft_arrlen(char **arr);
int			t_env_len(t_env *env);
int			t_inputs_len(t_inputs *inp);
char		*ft_strtrim(char *s1, char *set);
char		*ft_strtrim_free(char *s1, char *set);
char		*ft_substr(char *s, int start, int len);
char		**ft_arrjoin(char **arr1, char **arr2);
char		*ft_strreplace(char *str, char *replace);
char		**ft_split(char *s, char c);
char		**ft_split_equal(char *s);
void		print_header(void);
void		t_env_underscore_key_reset(t_env *env, char **args);
void		t_env_underscore_key_reset2(t_env *env, char *str);
int			t_env_exit_status_reset(t_env *env, int exit_status);

//==========================================================================
//	env_copy
//==========================================================================

t_env		*t_env_lstnew(char *str, int flag);
t_env		*t_env_lstlast(t_env *lst);
void		t_env_lstadd_back(t_env **lst, t_env *new);
t_env		*copy_environment(char **envp, char *prog_name);
int			ft_shlvl_max_check(int n);
void		t_env_change_val_and_flag(t_env *env, char *key, char *nv, int nf);
void		t_env_init_shlvl_and_underscore(t_env *env, char *str);
void		t_env_init_oldpwd(t_env *env);
char		*t_env_get_value_of_key(t_env *env, char *key);

//==========================================================================
//	t_data
//==========================================================================

void		t_data_update(t_data *d, t_env *env, t_inputs *inp);

//==========================================================================
//	builtins
//==========================================================================

void		pwd(t_data *d);
int			builtins(t_data *d, t_env **env, char **args, char *builtin);
int			single_builtins(t_data *d, t_env **env);
int			builtin_echo(t_data *d, char **args);
int			builtin_env(t_data *d, char **args);
int			builtin_export(t_data *d, char **args);
int			builtin_pwd(t_data *d, char **args);
int			builtin_unset(t_data *d, t_env **env, char **args);
int			builtin_cd(t_data *d, char **args);
int			builtin_exit(t_data *d, char **args);
void		ft_exit_check(t_data *d);

//==========================================================================
//	heredoc
//==========================================================================

void		ft_unlink(char *str, t_data *d);
void		unexp_token_check(t_data *d);
int			here_doc(t_data *d, char *limiter);
void		here_doc_max_check(t_data *d);
int			ft_open_heredocs(t_data *d);
int			ft_open_heredocs_for_proc(t_data *d, t_inputs **inp);

//==========================================================================
//	redirections
//==========================================================================

int			ft_open_redirs(t_data *d);
int			ft_open_redirs_for_proc(t_data *d, t_inputs **inp);

//==========================================================================
//	processes
//==========================================================================

void		close_pipes(t_data *d);
char		**get_path(t_data *d);
char		*check_cmd(char **path_arr, char *cmd);
char		**t_env_to_array(t_env *env);
void		ft_change_fdin(t_data *d);
void		ft_change_fdout(t_data *d);
void		ft_call_exeve(t_data *d);
void		call_process(t_data *d, int index);
int			create_pipes(t_data *d);
void		ft_close_fdin_and_fdout(int *fdin, int *fdout);
int			exec_processes(t_data *d, int index);
void		wait_for_children(t_data *d);

//==========================================================================
//	signals
//==========================================================================

void		handler_signals(int sig);
void		handler_signals2(int sig);
void		handler_signals3(int sig);

#endif
