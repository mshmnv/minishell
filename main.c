/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:23:45 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/06 15:06:35 by lbagg            ###   ########.fr       */
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
	env_data = (char**)malloc(sizeof(char*) * i);
	i = 0;
	while(envp[i])
	{
		env_data[i] = ft_strdup(envp[i]);
		i++;
	}
	env_data[i] = NULL;
	return(env_data);
}

int		shell_loop(char **env_data)
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
		// execute the commands
		launch(commands, env_data);
		// check status
		
		//free memory
		free(line);
		free_arr(commands);
		line = NULL;
	}
	return (status);
}

char	**read_commands(char *line)
{
	char	**commands;
	int		i;
	int		j;

	i  = 0;	
	j  = 0;
	// now only 1 command, later count commands
	commands = (char**)malloc(sizeof(char*) * 2);
	commands[i] = NULL;
	while (*line && *line != '|' && *line != ';')
	{
		if (!commands[i])
		{
			commands[i] = (char*)malloc(sizeof(char) * 2);
			commands[i][j] = *line;
			commands[i][j + 1] = '\0';
		}
		else
		{
			j = ft_strlen(commands[i]);
			commands[i] = ft_realloc(commands[i], j + 2);
			commands[i][j] = *line;
			commands[i][j + 1] = '\0';
		}
		line++;
	}
	i++;
	commands[i] = NULL;
	return(commands);
}
