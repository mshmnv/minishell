/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:56:31 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/19 14:19:35 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ctrl-\ - SIGQUIT
// ctrl-C - SIGINT
// ctrl-D - EOF

// SIG_IGN - ignore signal

// signal(int signum, sighandler);

void	ignore_signals()
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}

void	sigint(int sig)
{
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("shell > ", 1);
}

void	sigquit(int sig)
{
	
}
