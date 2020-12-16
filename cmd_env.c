/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:41:32 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/16 11:20:11 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_env(char **args, char **env_data)
{
	int i;

	i = 0;
	while (env_data[i])
	{
		if (ft_strchr(env_data[i], '='))
			ft_putendl_fd(env_data[i], 1);
		i++;
	}
	return (env_data);
}
