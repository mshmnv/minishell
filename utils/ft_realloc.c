/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 01:55:17 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/29 00:07:44 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_realloc(char *str, int len)
{
	char	*res;
	int		i;

	i = 0;
	res = NULL;
	if ((res = (char*)malloc(sizeof(char) * (len + 1))))
	{
		while (str && str[i])
		{
			res[i] = str[i];
			i++;
		}
		while (i <= len)
		{
			res[i] = '\0';
			i++;
		}
		free(str);
	}
	return (res);
}
