/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 17:23:48 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/30 23:21:11 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_quotes(char *line, char **command, t_command *tmp)
{
	int		i;
	int		j;
	char	quote;
	int		n;

	quote = line[0];
	i = 1;
	j = 0;
	if (*command)
		tmp->args = ft_strtok(*command, " \n\t");
	n = 0;
	if (tmp->args)
	{
		while (tmp->args[n])
			n++;
		tmp->args = ft_double_realloc(tmp->args, n + 1, "");
	}
	else
	{
		tmp->args = (char**)malloc(sizeof(char*) * 2);
		tmp->args[0] = NULL;
	}
	while (line[i] && line[i] != quote)
	{
		if (line[i] == '$' && quote == '"')
			i += parsing_env(line + i + 1, &tmp->args[n]);
		else
		{
			if (line[i] == '\\' && quote == '"'
				&& ft_strchr("$\\\"", line[i + 1]))
				i++;
			if (tmp->args[n])
				j = ft_strlen(tmp->args[n]);
			if (!(tmp->args[n]= ft_realloc(tmp->args[n], j + 1)))
				error(ER_MALLOC);
			tmp->args[n][j] = line[i];
		}
		i++;
	}
	return (i);
}
