/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_realloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 00:00:36 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/29 00:06:28 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	**ft_double_realloc(char **str, int len, char *line)
{
	char	**res;
	int		i;

	res = NULL;
	i = 0;
	if ((res = (char**)malloc(sizeof(char*) * (len + 1))))
	{
		while (str[i])
		{
			res[i] = ft_strdup(str[i]);
			i++;
		}
		res[i] = ft_strdup(line);
		res[i + 1] = NULL;
		free_arr(str);
	}
	return (res);
}
