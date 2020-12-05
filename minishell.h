/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:27:55 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/05 17:36:25 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <sys/types.h> 
# include <unistd.h>

# include <stdio.h>

char			**cmd_echo(char **tokens, char **data);
char			**cmd_cd(char **tokens, char **data);
char			**cmd_pwd(char **tokens, char **data);
char			**cmd_export(char **tokens, char **data);
char			**cmd_unset(char **tokens, char **data);
char			**cmd_env(char **tokens, char **data);
char			**cmd_exit(char **tokens, char **data);

typedef struct	s_builtin
{
	char		*name;
	char		**(*func)(char **tokens, char **env_data);
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

char			**read_envp(char **envp);
int				shell_loop(char **env_data);
char			**read_commands(char *line);
char			**launch(char **commands, char **env_data);
char 			**execute(char **tokens, char **env_data);
int 			execute_ps(char **tokens, char **env_data);
void			error(char *message);



# endif