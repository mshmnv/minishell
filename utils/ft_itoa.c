/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 13:22:57 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/29 00:07:06 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	ft_tensnum(int n)
{
	size_t i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char			*ft_itoa(int n)
{
	char	*res;
	size_t	minus;
	size_t	tens;
	int		des;
	size_t	i;

	i = 0;
	des = 1;
	minus = (n < 0) ? 1 : 0;
	tens = ft_tensnum(n);
	if (!(res = (char*)malloc(sizeof(char) * (tens + minus + 1))))
		return (NULL);
	if (minus)
		res[i++] = '-';
	while (tens-- > 1)
		des *= 10;
	while (des > 0)
	{
		res[i] = (n / des < 0) ? -(n / des) + '0' : n / des + '0';
		i++;
		n %= des;
		des /= 10;
	}
	res[i] = '\0';
	return (res);
}
