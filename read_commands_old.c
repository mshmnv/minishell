/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 22:44:02 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/17 21:33:13 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**read_commands(char *line)
{
	char	**commands;
	int		i;
	int		j;

	i = 0;	
	j = 0;
	commands = (char**)malloc(sizeof(char*));
	// commands[i] = (char*)malloc(sizeof(char));
	// commands[i][0] = '\0';
	commands[i] = NULL;
	while (*line)
	{
		if (*line == ';')
		{
			i++;
			j = 0;
			commands = ft_double_realloc(commands, i + 1, "");
		}
		else
		{
			j = ft_strlen(commands[i]);
			commands[i] = ft_realloc(commands[i], j + 1);
			commands[i][j] = *line;
			commands[i][j + 1] = '\0';
		}
		line++;
	}
	i++;
	commands[i] = NULL;
	// i = 0;
	// while (commands[i])
	// {
	// 	ft_putstr_fd("(", 1);
	// 	ft_putstr_fd(commands[i], 1);
	// 	ft_putendl_fd(")", 1);
	// 	i++;
	// }
	return(commands);
}