/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:27:55 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/30 21:56:54 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "utils/utils.h"
# include "get_next_line/get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>

# define PROMPT "shell > "
# define ER_FORK 0
# define ER_EXECUTE 1
# define ER_MALLOC 2
# define ER_FILE 3
# define ER_SYNTAX 4

typedef struct			s_builtin
{
	char				*name;
	void				(*func)(char **args);
}						t_builtin;

typedef struct			s_command
{
	char				*command;
	char				**args;
	int					pipe_flag;
	int					redir_flag;
	char				*in_fname;
	char				*out_fname;
	int					append;
	struct s_command	*next;
}						t_command;
/*
**		globals
*/
int						g_exit;
char					**g_env;
/*
** 		builtins
*/
void					cmd_echo(char **args);
void					cmd_cd(char **args);
void					cmd_pwd(char **args);
void					cmd_export(char **args);
void					cmd_unset(char **args);
void					cmd_env(char **args);
void					cmd_exit(char **args);
/*
**		main.c
*/
char					**read_envp(char **envp);
void					shell_loop();
/*
**		launch.c
*/
void					launch(t_command *cmds);
void					execute(char **args);
void					execute_process(char **args);
void					find_cmd(char **args);
/*
**		error.c
*/
void					error(int error);
void					error_errno();
void					error_no_cmd(char *arg);
void					error_exit(char *arg);
void					error_cd(char *arg);
/*
**		parsing.c
*/
int						parsing(char *line, t_command *cmds);
int						what_to_parse(char **line, t_command *tmp,
						char **command);
int						parse_next_command(char line_char, t_command **cmds);
int						parse_command(char **command, char *line);
int						check_syntax(char *command);
/*
**		parsing_env.c
*/
int						parsing_env(char *line, char **command);
int						env_symb_skip(char *env_str, char *line);
int						env_preparse(char *line, char **command);
/*
**		parsing_redirects.c
*/
int						parsing_redirects(char redir_symb, char *line,
						t_command *cmds);
/*
**		parsing_quotes.c
*/
int						parsing_quotes(char *line, char **command);
/*
**		signals.c
*/
void					handle_signals();
void					sigint(int sig);
void					sigquit(int sig);
void					handle_child_signals(int status);
void					ignore_signals();
/*
**		cmd_list.c
*/
t_command				*new_cmd_list();
void					free_cmd_list(t_command **cmds);
/*
**		pipes.c
*/
void					execute_pipe(char ***args, t_command **cmds);
void					fork_pipe(int save_fd, int *fd, char **args, t_command *cmds);
void					child_pipe(char **args, int *fd, int save_fd,
						t_command *cmds);					
/*
**		redirects.c
*/
void					execute_redirects(char **args, t_command *cmd);

#endif
