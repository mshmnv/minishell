/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 14:27:25 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/05 17:49:36 by lbagg            ###   ########.fr       */
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

char	**launch(char **commands, char **env_data)
{
	int		i;
	char	**tokens;
	int		status;
	
	status = 1;

	i = 0;
	while (commands[i])
	{

		tokens = ft_strtok(commands[i], " \t\n\t\a\"");
		env_data = execute(tokens, env_data);
		// free tokens
		// free commands[i]
		i++;
	}
	return (env_data);
}

char 	**execute(char **tokens, char **env_data)
{
	int i;

	i = 0;
	while (i < 7)
	{
		if (!(ft_strncmp(tokens[0], g_builtin[i].name, ft_strlen(g_builtin[i].name))))
			return((g_builtin[i].func(tokens, env_data)));
		i++;
	}
	// if access?? != -1 -> execute_ps()
	execute_ps(tokens, env_data);
	// else find_cmd()
	return (env_data);
}

int 	execute_ps(char **tokens, char **env_data)
{
	pid_t	pid;
	
	pid = fork();
	// ft_putstr_fd(ft_itoa(pid), 1);
	// ft_putstr_fd(tokens[0], 1);

	if (pid == 0) //child
	{
		if (execve(tokens[0], tokens, env_data) == -1)
			error("Failed to execute!");
	}
	else if (pid < 0)
		error("Failed to fork!");
	else
		wait(&pid);
	return (1);
}