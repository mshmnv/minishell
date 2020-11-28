/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 14:41:32 by lbagg             #+#    #+#             */
/*   Updated: 2020/11/27 21:11:53 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_env(char **tokens, char **env_data)
{
	int i;

	i = 0;	
	while (env_data[i])
	{
		ft_putendl_fd(env_data[i], 1);
		i++;
	}
	return (env_data);
}