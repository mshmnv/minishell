/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:07:10 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/01 00:23:36 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		skip_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int		parsing(char *line, t_command *cmds)
{
	t_command	*tmp;
	int			ret;

	tmp = cmds;
	while (*line)
	{
		if (ft_strchr("><\'\"$", *line))
		{
			if (!(what_to_parse(&line, tmp)))
				return (0);
		}
		else if (*line == '|' || *line == ';')
		{
			if (!parse_next_command(*line, &tmp))
				return (0);
			line++;
		}
		else
			line += parse_command(tmp, line);
	}
	return (1);
}

int		what_to_parse(char **line, t_command *cmd)
{
	int	ret;

	if (**line == '>' || **line == '<')
	{
		if ((ret = parsing_redirects(**line, *line + 1, cmd)) == -1)
			return (0);
		*line += ret;
	}
	else if (**line == '\'' || **line == '"')
		*line += parsing_quotes(*line, **line, cmd) + 1;
	else if (**line == '$')
		*line += parsing_env(*line + 1, cmd) + 1;
	return (1);
}

int		parse_next_command(char line_char, t_command **cmds)
{
	if (!(*cmds)->args[0])
	{
		error(ER_SYNTAX);
		return (0);
	}
	if (line_char == '|')
		(*cmds)->pipe_flag = 1;
	if ((*cmds)->args)
	{
		if (!((*cmds)->next = new_cmd_list()))
			error(ER_MALLOC);
		(*cmds) = (*cmds)->next;
	}
	return (1);
}

int		parse_command(t_command *cmd, char *line)
{
	int	j;
	int	i;
	int	n;
	int	next_arg;

	j = 0;
	i = 0;
	n = cmd->args_size - 1;
	if (line[i] == '\\')
		i++;
	if (*cmd->args)
		(cmd->args[n]) ? (j = ft_strlen(cmd->args[n])) : 0;
	if ((next_arg = skip_spaces(line)) && line[i + next_arg])
	{
		if (!ft_strchr("><;|", line[i + next_arg]) && (cmd->args[n]))
		{
			cmd->args = ft_double_realloc(cmd->args, cmd->args_size + 1, NULL);
			cmd->args_size++;
		}
		return (i + next_arg);
	}
	if (!(cmd->args[n] = ft_realloc(cmd->args[n], j + 1)))
		error(ER_MALLOC);
	cmd->args[n][j] = line[i];
	return (i + 1);
}
