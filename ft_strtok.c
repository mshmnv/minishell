/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:57:58 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/18 01:43:45 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_chars(char *s, char *delim)
{
	int	chars;
	int	i;

	chars = 0;
	while (s[chars])
	{
		i = 0;
		while (delim[i])
		{
			if (s[chars] == delim[i])
				return (chars);
			i++;
		}
		chars++;
	}
	return(chars);
}
static int	count_parts(char *s, char *delim)
{
	int		parts;
	int		i;
	
	parts = 1;
	while (*s)
	{
		i = 0;
		while (delim[i])
		{
			if(*s == delim[i])
				parts++;
			i++;
		}
		s++;
	}
	return(parts);
}

char		**ft_strtok(char *s, char *delim)
{
	char	**tok;
	int		parts;
	int		chars;
	int		i;
	int		j;

	if (!s || !*s)
		return (NULL);
	parts = count_parts(s, delim);
	tok = (char**)malloc(sizeof(char*) * (parts + 1));
	i = 0;
	while (i < parts)
	{
		j = 0;
		if (s)
		{
			if (!(chars = count_chars(s, delim)))
				s++;
			else
			{
				tok[i] = (char*)malloc(sizeof(char) * (chars + 1));
				while(*s && j < chars)
				{
					tok[i][j] = *s;
					s++;
					j++;
				}
				tok[i][j] = '\0';
				i++;
			}
		}
		if (!*s)
			break;
	}
	tok[i] = NULL;
	return (tok);
}