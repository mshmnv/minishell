/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:42:36 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/30 14:46:36 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**cmd_exit(char **args, char **env_data)
{
	int	i;

	ft_putendl_fd("exit", 1);
	i = 0;
	while (args[i])
		i++;
	if (i == 1)
		exit(EXIT_SUCCESS);
	if (i > 2)
		ft_putendl_fd("shell: exit: too many arguments", STDERR_FILENO);
	else if (i == 2)
	{
		i = 0;
		if (args[1][i] == '-' || args[1][i] == '+')
			i++;
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i]))
				error_exit(args[1]);
			i++;
		}
		exit(ft_atoi(args[1]) % 256);
	}
	return (env_data);
}
