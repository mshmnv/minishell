/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:23:45 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/15 14:13:39 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	char **env_data;
	
	env_data = read_envp(envp);
	shell_loop(env_data);
	return (0);
}

char	**read_envp(char **envp)
{
	char	**env_data;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
		i++;
	env_data = (char**)malloc(sizeof(char*) * (i + 1));
	i = 0;
	while(envp[i])
	{
		env_data[i] = ft_strdup(envp[i]);
		i++;
	}
	env_data[i] = NULL;
	return(env_data);
}

void	shell_loop(char **env_data)
{
	int		status;
	char	*line;
	char	**commands;
	int		ret;
	
	status = 1;
	line = NULL;
	while (status)
	{
		ft_putstr_fd("shell $> ", 1);
		get_next_line(0, &line);
		// split line on commands
		commands = read_commands(line);	
		// execute commands
		env_data = launch(commands, env_data);
		// check status
		// ... status = launch(commands, env_data);
		free(line);
		free_arr(commands);
		line = NULL;
	}
}
