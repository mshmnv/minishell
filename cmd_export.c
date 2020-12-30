/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:40:48 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/30 19:01:35 by lbagg            ###   ########.fr       */
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

static int	is_env(char *arg)
{
	char	*name;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (g_env[i])
	{
		j = 0;
		while (arg[j] && arg[j] != '=' && g_env[i][j]
				&& g_env[i][j] == arg[j])
			j++;
		if (arg[j] == '=')
		{
			tmp = g_env[i];
			g_env[i] = ft_strdup(arg);
			free(tmp);
			return (1);
		}
		else if (!arg[j] && g_env[i][j - 1] == arg[j - 1])
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
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(arg, 1);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			return (1);
		}
		j++;
	}
	return (0);
}

void		cmd_export(char **args)
{
	int		i;
	int		j;
	char	*last;

	if (!args[1])
		print_export(g_env);
	else
	{
		i = 1;
		while (args[i])
		{
			if (!error_name(args[i]) && !is_env(args[i]))
			{
				j = 0;
				while (g_env[j])
					j++;
				g_env = ft_double_realloc(g_env, j + 1, args[i]);
			}
			i++;
		}
	}
}
