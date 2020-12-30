/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:33:40 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/30 21:49:03 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_env(char *line, char **command)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	if ((env_preparse(line, command) == 1))
		return (1);
	while (g_env[i])
	{
		j = env_symb_skip(g_env[i], line);
		if (g_env[i][j] && g_env[i][j] == '=')
		{
			tmp = *command;
			if (!(*command = ft_strjoin(*command, g_env[i] + j + 1)))
				error(ER_MALLOC);
			free(tmp);
			return (j);
		}
		i++;
	}
	j = 0;
	while (ft_isalnum(line[j]) || line[j] == '_')
		j++;
	return (j);
}

int		env_symb_skip(char *env_str, char *line)
{
	int		j;

	j = 0;
	while (env_str[j] && line[j] &&\
		env_str[j] == line[j] && env_str[j] != '=')
		j++;
	return (j);
}

int		env_preparse(char *line, char **command)
{
	char	*tmp;
	char	*exit_code;

	if (line[0] == '?')
	{
		tmp = *command;
		exit_code = ft_itoa(g_exit);
		if (!(*command = ft_strjoin(*command, exit_code)))
			error(ER_MALLOC);
		free(tmp);
		free(exit_code);
		return (1);
	}
	if (!ft_isalpha(line[0]) && line[0] != '_')
		return (1);
	return (0);
}
