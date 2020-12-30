/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:41:32 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/30 18:58:49 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_env(char **args)
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
		while (g_env[i])
		{
			if (ft_strchr(g_env[i], '='))
				ft_putendl_fd(g_env[i], 1);
			i++;
		}
}
