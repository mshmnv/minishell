/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 15:31:16 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/29 18:04:38 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		cut_line(char **line, char **remainder)
{
	int		i;

	i = 0;
	while ((*remainder)[i] != '\n')
		i++;
	if (!(*line = (char*)malloc(sizeof(char) * (i + 1))))
		return (-1);
	ft_strlcpy(*line, *remainder, i + 1);
	return (0);
}

int		read_line(char **remainder, char **line)
{
	int		ret;
	char	*buf;
	int		res;
	char	*tmp;

	ret = 1;
	if (!(buf = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while (buf[0] != '\n' && ret != 0)
	{
		ret = read(0, buf, BUFFER_SIZE);
		buf[ret] = '\0';
		tmp = *remainder;
		if (!(*remainder = ft_strjoin(*remainder, buf)))
			return (-1);
		free(tmp);
		if (ret == 0 && (*remainder)[0] == 0)
		{
			write(1, "exit\n", 6);
			exit(0);
		}
		else if (ret == 0)
		{
			ret = 1;
			write(0, "  \b\b", 4);
		}
	}
	free(buf);
	res = cut_line(line, remainder);
	return (res);
}

int		get_next_line(char **line)
{
	int				out;
	char			*remainder;

	if (!line)
		return (-1);
	remainder = ft_strdup("");
	out = read_line(&remainder, line);
	free(remainder);
	return (out);
}
