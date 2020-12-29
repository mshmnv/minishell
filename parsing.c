/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:07:10 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/29 17:59:50 by student          ###   ########.fr       */
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

int		parse_redirects(char redir_symb, char *line, t_command *cmds)
{
	int		i;
	int		j;
	char	*fname;
	int		start;

	i = 0;
	j = 0;
	if (line[i] == '>')
	{
		i++;
		cmds->append = 1;
	}
	while (line[i] == ' ')
		i++;
	start = i;
	while (line[i] && line[i] != ' ')
	{
		i++;
		j++;
	}
	if (!(fname = (char*)malloc(sizeof(char) * (j + 1))))
		error(ER_MALLOC);
	ft_strlcpy(fname, line + start, j + 1);
	if (redir_symb == '>')
		cmds->out_fname = fname;
	else
		cmds->in_fname = fname;
	return ((line[i + 1] == '<' || line[i + 1] == '>') ? i + 2 : i);
}

int		parse_quotes(char **env_data, char *line, char **command)
{
	int		i;
	int		j;
	char	quote;


	quote = line[0];
	i = 1;
	j = 0;
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
			if (!(*command = ft_realloc(*command, j + 1)))
				error(ER_MALLOC);
			(*command)[j] = line[i];
		}
		i++;
	}
	return (i);	
}

int		parse_env_value(char **env_data, char *line, char **command)
{
	int		i;
	int 	j;
	char	*tmp;

	i = 0;
	if (line[i] == '?')
	{
		tmp = *command;
		if (!(*command = ft_strjoin(*command, ft_itoa(g_exit))))
			error(ER_MALLOC);
		free(tmp);
		return (1);
	}
	if (!ft_isalpha(line[i]) || line[i] != '_')
		return (1);
	while (env_data[i])
	{
		j = 0;
		while (env_data[i][j] && line[j] && env_data[i][j] == line[j] && env_data[i][j] != '=')
			j++;
		if (env_data[i][j] && env_data[i][j] == '=')
		{
			tmp = *command;
			if (!(*command = ft_strjoin(*command, env_data[i] + j + 1)))
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

void	parsing(char *line, t_command *cmds, char **env_data)
{
	char	*command;
	int		j;
	t_command *tmp;

	tmp = cmds;
	command = NULL;
	while (*line)
	{
		if (*line == '|' || *line == ';' || *line == '>' || *line == '<')
		{
			if (*line == '|')
				tmp->pipe_flag = 1;
			while (*line == '>' || *line == '<')
			{
				tmp->redir_flag = 1;
				line += parse_redirects(*line, line + 1, tmp);
			}
			tmp->command = command;
			command = NULL;
			if (!(tmp->next = new_cmd_list()))
				error(ER_MALLOC);
			tmp = tmp->next;
			line++;
		}
		else if (*line == '\'' || *line == '"')
			line += parse_quotes(env_data, line, &command) + 1;
		else if (*line == '$')
			line += parse_env_value(env_data, line + 1, &command) + 1;
		else
		{
			j = 0;
			if (*line == '\\')
				line++;
			if (command)
				j = ft_strlen(command);
			if (!(command = ft_realloc(command, j + 1)))
				error(ER_MALLOC);
			command[j] = *line;
			line++;
		}
	}
	tmp->command = command;
}