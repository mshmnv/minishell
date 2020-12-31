/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 16:33:40 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/31 23:59:58 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_env(char *line, t_command *cmd)
{
	int		i;
	int		j;
	int		n;
	char	*tmp;

	n = cmd->args_size - 1;
	if ((env_preparse(line, &cmd->args[n]) == 1))
		return (1);
	i = -1;
	while (g_env[++i])
	{
		if ((j = env_symb_skip(g_env[i], line, i)))
		{
			tmp = cmd->args[n];
			if (!(cmd->args[n] = ft_strjoin(cmd->args[n],
				g_env[i] + j + 1)))
				error(ER_MALLOC);
			free(tmp);
			return (j);
		}
	}
	j = 0;
	while (ft_isalnum(line[j]) || line[j] == '_')
		j++;
	return (j);
}

int		env_symb_skip(char *env_str, char *line, int i)
{
	int	j;

	j = 0;
	while (env_str[j] && line[j] &&
		env_str[j] == line[j] && env_str[j] != '=')
		j++;
	if (g_env[i][j] && g_env[i][j] == '=')
		return (j);
	return (0);
}

int		env_preparse(char *line, char **arg)
{
	char	*tmp;
	char	*exit_code;

	if (line[0] == '?')
	{
		tmp = *arg;
		exit_code = ft_itoa(g_exit);
		if (!(*arg = ft_strjoin(*arg, exit_code)))
			error(ER_MALLOC);
		free(tmp);
		free(exit_code);
		return (1);
	}
	if (!ft_isalpha(line[0]) && line[0] != '_')
		return (1);
	return (0);
}
