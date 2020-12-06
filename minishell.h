/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:27:55 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/06 19:18:17 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <sys/types.h> 
# include <unistd.h>

#include <sys/stat.h>

# include <stdio.h>

void			cmd_echo(char **args, char **data);
void			cmd_cd(char **args, char **data);
void			cmd_pwd(char **args, char **data);
void			cmd_export(char **args, char **data);
void			cmd_unset(char **args, char **data);
void			cmd_env(char **args, char **data);
void			cmd_exit(char **args, char **data);

typedef struct	s_builtin
{
	char		*name;
	void		(*func)(char **args, char **env_data);
}				t_builtin;

// t_builtin		g_builtin[] =
// {
// 	{"echo", &cmd_echo},
// 	{"cd", &cmd_cd},
// 	{"pwd", &cmd_pwd},
// 	{"export", &cmd_export},
// 	{"unset", &cmd_unset},
// 	{"env", &cmd_env},
// 	{"exit", &cmd_exit},
// };

// will be moved to libft
char			*ft_realloc(char *str, int len);
char			**ft_strtok(char *s, char *delim);
void			free_arr(char **arr);

char			**read_envp(char **envp);
int				shell_loop(char **env_data);
char			**read_commands(char *line);
void			launch(char **commands, char **env_data);
void			execute(char **args, char **env_data);
void 			execute_process(char **args, char **env_data);
void			error(char *message);



# endif