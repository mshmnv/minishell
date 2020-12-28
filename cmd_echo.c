/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 17:57:52 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/28 23:30:57 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		**cmd_echo(char **args, char **env_data)
{
	int i;
	int n_flag;

	n_flag = 0;
	if (args[1])
	{
		i = 1;
		while (!ft_strncmp(args[i], "-n", 2))
		{
			n_flag = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1])
				ft_putchar_fd(' ', 1);
			i++;
		}
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	return (env_data);
}
