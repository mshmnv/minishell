/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:23:45 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/27 16:38:58 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	char **env_data;
	
	env_data = read_envp(envp);
	g_error = 0;
	handle_signals();
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
	if (!(env_data = (char**)malloc(sizeof(char*) * (i + 1))))
		error(ER_MALLOC);
	i = 0;
	while(envp[i])
	{
		if (!(env_data[i] = ft_strdup(envp[i])))
			error(ER_MALLOC);
		i++;
	}
	env_data[i] = NULL;
	return(env_data);
}



void	shell_loop(char **env_data)
{
	char		*line;
	t_command	*cmds;
	t_all		*all;
	
	line = NULL;
	all->env_data = env_data;
	while (21)
	{
		cmds = new_cmd_list();
		all->cmds = cmds;
		ft_putstr_fd(PROMPT, 1);
		get_next_line(0, &line);
		parsing(line, cmds, all->env_data);
		launch(all);
		free_cmd_list(&cmds);
		free(line);
		line = NULL;
	}
}
