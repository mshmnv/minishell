/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:23:45 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/31 11:07:26 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **envp)
{
	g_env = read_envp(envp);
	g_exit = 0;
	handle_signals();
	shell_loop();
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
	while (envp[i])
	{
		if (!(env_data[i] = ft_strdup(envp[i])))
			error(ER_MALLOC);
		i++;
	}
	env_data[i] = NULL;
	return (env_data);
}

void	shell_loop(void)
{
	char		*line;
	t_command	*cmds;

	line = NULL;
	while (21)
	{
		cmds = new_cmd_list();
		ft_putstr_fd(PROMPT, 1);
		get_next_line(&line);
		if (parsing(line, cmds))
			launch(cmds);
		free_cmd_list(&cmds);
		free(line);
		line = NULL;
	}
}
