/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:56:31 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/27 20:42:01 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	// if (g_signal == 7)
	// {
	// 	g_signal = 8;
	// 	ft_putstr("\n");
	// 	return ;
	// }
	// if (g_signal == 2)
	// {
	// 	g_signal = 1;
	// 	ft_putstr("\n");
	// 	return ;
	// }

// ctrl-\ - SIGQUIT
// ctrl-C - SIGINT
// ctrl-D - EOF

// SIG_IGN - ignore signal

// signal(int signum, sighandler);

void	ignore_signals()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_child_signals()
{
	signal(SIGINT, child_signals);
	signal(SIGQUIT, child_signals);
}

void	child_signals(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd(PROMPT, 1);
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
	}
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
}

void	sigquit(int sig)
{
	write(0, "\b\b  \b\b", 6);
}
