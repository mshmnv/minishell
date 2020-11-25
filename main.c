/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 16:23:45 by lbagg             #+#    #+#             */
/*   Updated: 2020/11/25 01:57:14 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute(char **commands)
{
	
}

char **read_commands(char *line)
{
	char	**commands;
	int		i;
	int		j;

	i  = 0;	
	j  = 0;	
	commands = (char**)malloc(sizeof(char*) * 2);
	commands[i] = NULL;
	while (*line && *line != '|' && *line != ';')
	{
		// printf("AA");
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
	return(commands);
}

void	shell_loop()
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
		if ((ret = get_next_line(1, &line)) > 0)
		{
			// split line on commands
			commands = read_commands(line);
			
			printf("(%s)\n", commands[0]);
			// execute the commands
			// status = execute(commands);
			
			//free memory
			free(line);
			// if (*commands)
			// while (*commands)
			// {
			// 	free(*commands);
			// 	commands++;
			// }
			// free(commands);
		}
	}
}

int		main(int argc, char **argv, char **envp)
{
	shell_loop();
	return (0);
}
