/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 17:27:55 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/16 11:32:20 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <sys/types.h> 
# include <unistd.h>
# include <sys/stat.h>

# include <stdio.h>

char			**cmd_echo(char **args, char **env_data);
char			**cmd_cd(char **args, char **env_data);
char			**cmd_pwd(char **args, char **env_data);
char			**cmd_export(char **args, char **env_data);
char			**cmd_unset(char **args, char **env_data);
char			**cmd_env(char **args, char **env_data);
char			**cmd_exit(char **args, char **env_data);

typedef struct	s_builtin
{
	char		*name;
	char		**(*func)(char **args, char **env_data);
}				t_builtin;

// will be moved to libft
char			*ft_realloc(char *str, int len);
char			**ft_double_realloc(char **str, int len, char *line);
char			**ft_strtok(char *s, char *delim);
void			free_arr(char **arr);

char			**read_envp(char **envp);
void			shell_loop(char **env_data);
char			**read_commands(char *line);
char			**launch(char **commands, char **env_data);
char			**execute(char **args, char **env_data);
void 			execute_process(char **args, char **env_data);
void			find_cmd(char **args, char **env_data);
void			error(char *message);



# endif