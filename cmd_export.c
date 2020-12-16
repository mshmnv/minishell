/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:40:48 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/16 11:30:53 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**sort_env(char **env_data, int len)
{
	int		i;
	int		j;
	char	**new;
	char	*tmp;

	new = (char**)malloc(sizeof(char*) * (len + 1));
	new[len] = NULL;
	i = -1;
	while (env_data[++i])
		new[i] = ft_strdup(env_data[i]);
	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j < len - 1)
		{
			if (ft_strncmp(new[j], new[j + 1], ft_strlen(new[j]) + 1) > 0)
			{
				tmp = new[j + 1];
				new[j + 1] = new[j];
				new[j] = tmp;
			}
		}
	}
	return (new);
}

static void	print_export(char **env_data)
{
	char	**sorted;
	int		i;
	int		j;

	i = 0;
	while (env_data[i])
		i++;
	sorted = sort_env(env_data, i);
	i = -1;
	while (sorted[++i])
	{
		ft_putstr_fd("declare -x ", 1);
		j = 0;
		while (sorted[i][j] && sorted[i][j] != '=')
			ft_putchar_fd(sorted[i][j++], 1);
		if (sorted[i][j])
		{
			ft_putchar_fd(sorted[i][j++], 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(sorted[i] + j, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
	}
	free_arr(sorted);
}

static int	is_env(char *arg, char **env_data)
{
	char	*name;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (env_data[i])
	{
		j = 0;
		while (arg[j] && arg[j] != '=' && env_data[i][j]
				&& env_data[i][j] == arg[j])
			j++;
		if (arg[j] == '=')
		{
			tmp = env_data[i];
			env_data[i] = ft_strdup(arg);
			free(tmp);
			return (1);
		}
		else if (!arg[j] && env_data[i][j - 1] == arg[j - 1])
			return (1);
		i++;
	}
	return (0);
}

static int	error_name(char *arg)
{
	int	j;

	j = 0;
	while ((arg[j] && arg[j] != '=') || (arg[j] == '=' && j == 0))
	{
		if (ft_isdigit(arg[0]) ||
			(!ft_isalpha(arg[j]) && !ft_isdigit(arg[j]) && arg[j] != '_'))
		{
			ft_putstr_fd("minishell: export: `", 1);
			ft_putstr_fd(arg, 1);
			ft_putendl_fd("': not a valid identifier", 1);
			return (1);
		}
		j++;
	}
	return (0);
}

char		**cmd_export(char **args, char **env_data)
{
	int		i;
	int		j;
	char	*last;

	if (!args[1])
		print_export(env_data);
	else
	{
		i = 1;
		while (args[i])
		{
			if (!error_name(args[i]) && !is_env(args[i], env_data))
			{
				j = 0;
				while (env_data[j])
					j++;
				env_data = ft_double_realloc(env_data, j + 1, args[i]);
			}
			i++;
		}
	}
	return (env_data);
}
