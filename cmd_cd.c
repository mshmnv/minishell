/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:40:13 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/28 15:04:10 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_env(char **env_data, char *oldir, char *dir)
{
	int		j;
	char	*tmp;

	j = 0;
	while (env_data[j])
	{
		if (ft_strnstr(env_data[j], "PWD=", 5))
		{
			tmp = env_data[j];
			env_data[j] = ft_strjoin("PWD=", dir);
			free(tmp);
		}
		else if (ft_strnstr(env_data[j], "OLDPWD=", 7))
		{
			tmp = env_data[j];
			env_data[j] = ft_strjoin("OLDPWD=", oldir);
			free(tmp);
		}
		j++;
	}
}

static char	*go_home(char **env_data)
{
	int	j;

	j = 0;
	while (env_data[j])
	{
		if (ft_strnstr(env_data[j], "HOME=", 5))
			return (env_data[j] + 5);
		j++;
	}
	return (NULL);
}

char		**cmd_cd(char **args, char **env_data)
{
	int			i;
	struct stat	stats;
	char		*dir;
	char		*oldir;

	oldir = getcwd(NULL, 0);
	if (!args[1])
		dir = go_home(env_data);
	else
		dir = args[1];
	if (stat(dir, &stats) == 0)
	{
		chdir(dir);
		dir = getcwd(NULL, 0);
		change_env(env_data, oldir, dir);
	}
	else
		error_cd(dir);
	free(oldir);
	return (env_data);
}
