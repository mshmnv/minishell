/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:40:13 by lbagg             #+#    #+#             */
/*   Updated: 2021/01/02 14:49:18 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_env(char *oldir, char *dir)
{
	int		j;
	char	*tmp;

	j = 0;
	while (g_env[j])
	{
		if (ft_strnstr(g_env[j], "PWD=", 5))
		{
			tmp = g_env[j];
			g_env[j] = ft_strjoin("PWD=", dir);
			free(tmp);
		}
		else if (ft_strnstr(g_env[j], "OLDPWD=", 7))
		{
			tmp = g_env[j];
			g_env[j] = ft_strjoin("OLDPWD=", oldir);
			free(tmp);
		}
		j++;
	}
}

static char	*go_home(void)
{
	int	j;

	j = 0;
	while (g_env[j])
	{
		if (ft_strnstr(g_env[j], "HOME=", 5))
			return (g_env[j] + 5);
		j++;
	}
	return (NULL);
}

void		cmd_cd(char **args)
{
	int			i;
	struct stat	stats;
	char		*dir;
	char		*oldir;

	oldir = getcwd(NULL, 0);
	if (!args[1])
		dir = go_home();
	else
		dir = args[1];
	if (stat(dir, &stats) == 0)
	{
		chdir(dir);
		dir = getcwd(NULL, 0);
		change_env(oldir, dir);
		free(dir);
	}
	else
		error_cd(dir);
	free(oldir);
}
