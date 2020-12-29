/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:56:31 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/29 16:30:23 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child_signals(int status)
{
	if (WTERMSIG(status) == 2)
		g_exit = 130;
	if (WTERMSIG(status) == 3)
	{
		ft_putstr_fd("Quit: 3", 1);
		g_exit = 131;
	}
	ft_putchar_fd('\n', 1);
}

void	ignore_signals()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_signals()
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}

void	sigint(int sig)
{
	write(0, "\b\b  \b\b", 6);
	write(0, "\n", 1);
	ft_putstr_fd(PROMPT, 1);
	g_exit = 1;
}

void	sigquit(int sig)
{
	write(0, "\b\b  \b\b", 6);
	g_exit = 0;
}
