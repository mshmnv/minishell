/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 14:27:25 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/19 14:36:21 by lbagg            ###   ########.fr       */
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

char	**launch(t_command *cmds, char **env_data)
{
	t_command	*tmp;
	int		i;
	char	**args;	

	i = 0;
	tmp = cmds;
	while (tmp)
	{
		// args = ft_strtok(tmp->command, " \t\n\t\a");
		if ((args = ft_strtok(tmp->command, " \n\t")))
		{
			env_data = execute(args, env_data);
			free_arr(args);
		}
		tmp = tmp->next;
	}
	return (env_data);
}

void	find_cmd(char **args, char **env_data) // leaks !!
{
	char	**path;
	int		i;
	char	*tmp;
	char	*new;
	struct stat stats;

	i = 0;
	while (env_data[i] && !(ft_strnstr(env_data[i], "PATH=", 5)))
		i++;
	if (!env_data[i])
		return ;
	path = ft_strtok(env_data[i] + 5, ":");
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
			free_arr(path);
			execute_process(args, env_data);
			return ;
		}
		i++;
		free(new);
	}
	free_arr(path);
	ft_putstr_fd("minishell: command not found: ", 1);
	ft_putendl_fd(args[0], 1);
}

char	**execute(char **args, char **env_data)
{
	int			i;
	struct stat	stats;

	i = 0;
	while (i < 7)
	{
		if (!(ft_strncmp(args[0], g_builtin[i].name, ft_strlen(g_builtin[i].name))))
			return (g_builtin[i].func(args, env_data));		
		i++;
	}
	if (stat(args[0], &stats) == 0)
		execute_process(args, env_data);
	else
		find_cmd(args, env_data);
	return (env_data);
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