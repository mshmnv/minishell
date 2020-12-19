/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:23:45 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/19 13:45:20 by lbagg            ###   ########.fr       */
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
	char	*line;
	char	**commands;
	int		ret;
	t_command	*cmds;
	
	line = NULL;
	// ignore_signals();
	while (21)
	{
		cmds = new_cmd_list();
		ft_putstr_fd("shell > ", 1);
		get_next_line(0, &line);
		parsing(line, cmds, env_data);

		env_data = launch(cmds, env_data);
		free_cmd_list(&cmds);
		// free(cmds->command);
		// free(cmds);
	
		free(line);
		line = NULL;
	}
}
