/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:40:13 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/10 19:18:55 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_env(char **env_data, char *oldir, char *dir) // change PWD OLDPWD
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

void		cmd_cd(char **args, char **env_data)
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
		change_env(env_data, oldir, dir);
	}
	else
	{
		ft_putstr_fd("cd: no such file or directory: ", 1);
		ft_putendl_fd(dir, 1);
	}
	free(oldir);
}
