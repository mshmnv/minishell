/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 14:27:25 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/06 19:25:28 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_builtin		g_builtin[] =
{
	{"echo", &cmd_echo},
	{"cd", &cmd_cd},
	{"pwd", &cmd_pwd},
	{"export", &cmd_export},
	{"unset", &cmd_unset},
	{"env", &cmd_env},
	{"exit", &cmd_exit},
};

void	launch(char **commands, char **env_data)
{
	int		i;
	char	**args;
	int		status;
	
	status = 1;

	i = 0;
	while (commands[i])
	{
		args = ft_strtok(commands[i], " \t\n\t\a");
		execute(args, env_data);
		free_arr(args);
		i++;
	}
}

void	find_cmd(char **args, char **env_data)
{
	char	*start;
	char	**path;
	int		i;
	char	*tmp;
	char	*new;
	struct stat stats;

	i = 0;
	while (!(start = ft_strnstr(env_data[i], "PATH=", 5)))
		i++;
	if (!start)
		return ;
	path = ft_strtok(start + 5, ":");
	i = 0;
	while (path[i])
	{
		tmp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(tmp);
		new = ft_strjoin(path[i], args[0]);
		if (stat(new, &stats) == 0)
		{
			tmp = args[0];
			args[0] = new;
			free(tmp);
			execute_process(args, env_data);
			return ;
		}
		i++;
		free(new);
	}
	free_arr(path);
}

void	execute(char **args, char **env_data)
{
	int		i;
	struct stat stats;

	i = 0;
	while (i < 7)
	{
		if (!(ft_strncmp(args[0], g_builtin[i].name, ft_strlen(g_builtin[i].name))))
		{
			g_builtin[i].func(args, env_data);
			return ;
		}
		i++;
	}
	if (stat(args[0], &stats) == 0)
		execute_process(args, env_data);
	else
		find_cmd(args, env_data);
}

void 	execute_process(char **args, char **env_data)
{
	pid_t	pid;
	
	pid = fork();
	if (pid == 0) // child has 0 returned
	{
		if (execve(args[0], args, env_data) == -1)
			error("Failed to execute!");
	}
	else if (pid < 0)
		error("Failed to fork!");
	else
		wait(&pid);
}