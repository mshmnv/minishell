/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 17:23:48 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/30 18:36:44 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_quotes(char *line, char **command)
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
			i += parsing_env(line + i + 1, command);
		else
		{
			if (line[i] == '\\' && quote == '"'
				&& ft_strchr("$\\\"", line[i + 1]))
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
