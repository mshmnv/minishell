/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:41:32 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/29 21:10:24 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_env(char **args, char **env_data)
{
	int i;

	i = 0;
	if (args[1])
	{
		g_exit = 127;
		ft_putstr_fd("shell: ", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	else
		while (env_data[i])
		{
			if (ft_strchr(env_data[i], '='))
				ft_putendl_fd(env_data[i], 1);
			i++;
		}
	return (env_data);
}
