/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:27:55 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/24 22:36:19 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <sys/types.h> 
# include <unistd.h>
# include <sys/stat.h>
# include <signal.h>
#include <fcntl.h>

# include <stdio.h>

# define PROMPT "shell > "

typedef struct	s_builtin
{
	char		*name;
	char		**(*func)(char **args, char **env_data);
}				t_builtin;

typedef struct				s_command
{
		char				*command;
		int					pipe_flag;
		int					redir_flag;
		char				*in_fname;
		char				*out_fname;
		int					file;
		int					append;
		struct s_command	*next;
}							t_command;

typedef struct				s_all
{
	char					**env_data;
	t_command				*cmds;
}							t_all;

/*
 * builtins
 */
char			**cmd_echo(char **args, char **env_data);
char			**cmd_cd(char **args, char **env_data);
char			**cmd_pwd(char **args, char **env_data);
char			**cmd_export(char **args, char **env_data);
char			**cmd_unset(char **args, char **env_data);
char			**cmd_env(char **args, char **env_data);
char			**cmd_exit(char **args, char **env_data);
/*
 * will be moved to libft
 */
char			*ft_realloc(char *str, int len);
char			**ft_double_realloc(char **str, int len, char *line);
char			**ft_strtok(char *s, char *delim);
void			free_arr(char **arr);
/*
 * main.c
 */
char			**read_envp(char **envp);
void			shell_loop(char **env_data);
/*
 * launch.c
 */
void			launch(t_all *all);
void			execute(char **args, t_all *all);
void 			execute_process(char **args, t_all *all);
void			find_cmd(char **args, char **env_data, t_all *all);
/*
 * error.c
 */
void			error(char *message);
/*
 * parsing.c
 */
void			parsing(char *line, t_command *cmds, char **env_data);
int				parse_env_value(char **env_data, char *line, char **command);
int				parse_quotes(char **env_data, char *line, char **command);
int				parse_redirects(char redir_symb, char *line, t_command *cmds);
char			is_any_symb(char ch, char *to_find);
/*
 * signals.c
 */
void			ignore_signals();
void			sigint(int sig);
void			sigquit(int sig);
/*
 * cmd_list.c
 */
t_command		*new_cmd_list();
void			free_cmd_list(t_command **cmds);

/*
 * pipes.c
 */
void			execute_pipe(char ***args, t_all *all, t_command **cmds);
void			child_pipe(char **args, int *fd, int save_fd, t_all *all);
/*
 * redirects.c
 */
void			execute_redirects(char **args, t_command *cmd, t_all *all);

# endif