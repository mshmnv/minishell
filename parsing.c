/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:07:10 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/20 17:35:11 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	is_any_symb(char ch, char *to_find)
{
	int	i;

	i = 0;
	while (to_find[i])
	{
		if (ch == to_find[i])
			return (to_find[i]);
		i++;
	}
	return ('\0');
}


int		parse_quotes(char **env_data, char *line, char **command)
{
	int		i;
	int		j;
	char	quote;

	quote = line[0];
	i = 1;
	while (line[i] && line[i] != quote)
	{
		if (line[i] == '$' && quote == '"')
			i += parse_env_value(env_data, line + i + 1, command);
		else
		{
			if (line[i] == '\\' && quote == '"' && is_any_symb(line[i + 1], "$\\\""))
				i++;
			if (*command)
				j = ft_strlen(*command);
			*command = ft_realloc(*command, j + 1);
			(*command)[j] = line[i];
		}
		i++;	
	}
	if (line[i] == quote)
		return (i);
	return (i);	
}

int		parse_env_value(char **env_data, char *line, char **command)
{
	int		i;
	int 	j;
	char	*tmp;

	i = 0;
	while (env_data[i])
	{
		j = 0;
		while (env_data[i][j] && line[j] && env_data[i][j] == line[j] && env_data[i][j] != '=')
			j++;
		if (env_data[i][j] && env_data[i][j] == '=')
		{
			tmp = *command;
			*command = ft_strjoin(*command, env_data[i] + j + 1);
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

void	parsing(char *line, t_command *cmds, char **env_data)
{
	char	*command;
	int		j;
	t_command *tmp;

	tmp = cmds;
	j = 0;
	command = NULL;
	while (*line)
	{
		if (*line == '|' || *line == ';')
		{
			if (*line == '|')
				tmp->pipe_flag = 1;
			tmp->command = command;
			command = NULL;
			tmp->next = new_cmd_list();
			tmp = tmp->next;
			line++;
		}
		else if (*line == '\'' || *line == '"')
			line += parse_quotes(env_data, line, &command) + 1;
		else if (*line == '$')
			line += parse_env_value(env_data, line + 1, &command) + 1;
		else
		{
			if (*line == '\\')
				line++;
			if (command)
				j = ft_strlen(command);
			command = ft_realloc(command, j + 1);
			command[j] = *line;
			line++;
		}
	}
	tmp->command = command;
}