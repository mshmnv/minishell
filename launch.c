/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 14:27:25 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/27 20:42:15 by lbagg            ###   ########.fr       */
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

void	launch(t_all *all)
{
	t_command	*tmp;
	int			i;
	char		**args;

	i = 0;
	tmp = all->cmds;
	while (tmp)
	{
		if ((args = ft_strtok(tmp->command, " \n\t")))
		{
			if (tmp->pipe_flag)
				execute_pipe(&args, all, &tmp);
			else if (tmp->redir_flag)
				execute_redirects(args, tmp, all);
			else
				execute(args, all);
			free_arr(args);
		}
		tmp = tmp->next;
	}
}

void	find_cmd(char **args, char **env_data, t_all *all)
{
	char		**path;
	int			i;
	char		*tmp;
	char		*new;
	struct stat	stats;

	i = 0;
	while (env_data[i] && !(ft_strnstr(env_data[i], "PATH=", 5)))
		i++;
	if (!env_data[i])
		return ;
	if (!(path = ft_strtok(env_data[i] + 5, ":")))
		error(ER_MALLOC);
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
			execute_process(args, all);
			return ;
		}
		i++;
		free(new);
	}
	free_arr(path);
	error_no_cmd(args[0]);
}

void	execute(char **args, t_all *all)
{
	int			i;
	struct stat	stats;

	i = 0;
	while (i < 7)
	{
		if (!(ft_strncmp(args[0], g_builtin[i].name, ft_strlen(g_builtin[i].name))))
		{
			all->env_data = g_builtin[i].func(args, all->env_data);
			return ;
		}
		i++;
	}
	if (stat(args[0], &stats) == 0)
		execute_process(args, all);
	else
		find_cmd(args, all->env_data, all);
}

void 	execute_process(char **args, t_all *all)
{
	pid_t	pid;
	int		status;

	ignore_signals();
	if ((pid = fork()) < 0)
		error(ER_FORK);
	if (pid == 0)
	{
		handle_child_signals();
		if (execve(args[0], args, all->env_data) == -1)
			error(ER_EXECUTE);
	}
	else
	{
		wait(&status);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == 2)  // ctrl-C
				g_error = 130;
			if (WTERMSIG(status) == 3)  // ctrl-"\"
				g_error = 131;
			write(1, "\n", 1);
		}
		else
			g_error = WEXITSTATUS(status);
		handle_signals();
	}
}