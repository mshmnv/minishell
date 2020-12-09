/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:57:52 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/10 00:37:45 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void check_env(char *arg, char **env_data)
{
	int j;

	j = 0;
	while (env_data[j])
	{
		if (ft_strnstr(env_data[j], arg + 1, ft_strlen(arg + 1))
			&& env_data[j][ft_strlen(arg + 1)] == '=')
		{
			ft_putstr_fd(env_data[j] + ft_strlen(arg + 1) + 1, 1);
			break ;
		}
		j++;
	}
}

void	cmd_echo(char **args, char **env_data)
{
	int i;
	int n_flag;

	n_flag = 0;
	if (!args[1])
		ft_putchar_fd('\n', 1);
	else if (args[1])
	{
		i = 1;
		if (!ft_strncmp(args[1], "-n", 2))
		{	
			n_flag = 1;
			i++;	
		}
		while(args[i])
		{
			if (args[i][0] == '$')
				check_env(args[i], env_data);
			else
				ft_putstr_fd(args[i], 1);
			if (args[i + 1])
				ft_putchar_fd(' ', 1);
			else if (!args[i + 1] && !n_flag)
				ft_putchar_fd('\n', 1);
			i++;
		}
	}
}
