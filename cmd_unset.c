/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:41:12 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/30 14:47:21 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_name(char *arg)
{
	int	j;

	j = 0;
	while (arg[j])
	{
		if (ft_isdigit(arg[0]) ||
			(!ft_isalpha(arg[j]) && !ft_isdigit(arg[j]) && arg[j] != '_'))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(arg, 1);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (1);
		}
		j++;
	}
	return (0);
}

char		**change_env(char **env_data, int what_unset)
{
	char	**new;
	int		i;

	i = 0;
	while (env_data[i])
		i++;
	new = (char**)malloc(sizeof(char*) * (i + 1));
	i = 0;
	while (i < what_unset)
	{
		new[i] = ft_strdup(env_data[i]);
		i++;
	}
	what_unset++;
	while (env_data[what_unset])
	{
		new[i] = env_data[what_unset];
		what_unset++;
		i++;
	}
	new[i] = NULL;
	free_arr(env_data);
	return (new);
}

char		**cmd_unset(char **args, char **env_data)
{
	int		i;
	int		j;

	i = 1;
	if (!args[1])
		ft_putendl_fd("unset: not enough arguments", STDERR_FILENO);
	while (args[i])
	{
		j = 0;
		while (!error_name(args[i]) && env_data[j])
		{
			if (ft_strnstr(env_data[j], args[i], ft_strlen(args[i])))
			{
				env_data = change_env(env_data, j);
				break ;
			}
			j++;
		}
		i++;
	}
	return (env_data);
}
