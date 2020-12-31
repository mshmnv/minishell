/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 17:23:48 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/01 01:04:48 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_quotes(char *line, char quote, t_command *cmd)
{
	int		i;
	int		j;
	int		n;

	j = 0;
	n = cmd->args_size - 1;
	i = 0;
	while (line[++i] && line[i] != quote)
	{
		if (line[i] == '$' && quote == '"')
			i += parsing_env(line + i + 1, cmd);
		else
		{
			if (line[i] == '\\' && quote == '"'
				&& ft_strchr("$\\\"", line[i + 1]))
				i++;
			if (cmd->args[n])
				j = ft_strlen(cmd->args[n]);
			if (!(cmd->args[n] = ft_realloc(cmd->args[n], j + 1)))
				error(ER_MALLOC);
			cmd->args[n][j] = line[i];
		}
	}
	(i == 1) ? (cmd->args[n] = ft_strdup("")) : 0;
	return (i);
}
