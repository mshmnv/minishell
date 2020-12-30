/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:07:10 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/30 22:18:11 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing(char *line, t_command *cmds)
{
	t_command	*tmp;
	int			ret;

	tmp = cmds;
	while (*line)
	{
		if (ft_strchr("><\'\"$", *line))
		{
			if (!(what_to_parse(&line, tmp, &tmp->command)))
				return (0);
		}
		else if (*line == '|' || *line == ';')
		{
			if (!parse_next_command(*line, &tmp))
				return (0);
			line++;
		}
		else
			line += parse_command(&tmp->command, line);
	}
	if (!tmp->args)
		tmp->args = ft_strtok(tmp->command, " \n\t");
	return (1);
}

int		what_to_parse(char **line, t_command *tmp, char **command)
{
	int	ret;

	if (**line == '>' || **line == '<')
	{
		if ((ret = parsing_redirects(**line, *line + 1, tmp)) == -1)
			return (0);
		*line += ret;
	}
	else if (**line == '\'' || **line == '"')
		*line += parsing_quotes(*line, command, tmp) + 1;
	else if (**line == '$')
		*line += parsing_env(*line + 1, command) + 1;
	return (1);
}

int		parse_next_command(char line_char, t_command **cmds)
{
	if (!check_syntax((*cmds)->command))
		return (0);
	if (line_char == '|')
		(*cmds)->pipe_flag = 1;
	if ((*cmds)->command)
	{
		if (!(*cmds)->args)
			(*cmds)->args = ft_strtok((*cmds)->command, " \n\t");
		if (!((*cmds)->next = new_cmd_list()))
			error(ER_MALLOC);
		(*cmds) = (*cmds)->next;
	}
	return (1);
}

int		check_syntax(char *command)
{
	int		i;

	i = 0;
	if (command)
		while (command[i])
		{
			if (!ft_strchr(" \n\t", command[i]))
				return (1);
			i++;
		}
	error(ER_SYNTAX);
	return (0);
}

int		parse_command(char **command, char *line)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (line[i] == '\\')
		i++;
	if (*command)
		j = ft_strlen(*command);
	if (!(*command = ft_realloc(*command, j + 1)))
		error(ER_MALLOC);
	(*command)[j] = line[i];
	return (i + 1);
}
