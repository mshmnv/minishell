/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbagg <lbagg@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:56:31 by lbagg             #+#    #+#             */
/*   Updated: 2020/12/16 15:27:10 by lbagg            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ctrl-\ - SIGQUIT
// ctrl-C - SIGINT
// ctrl-D - EOF

// signal(int signum, sighandler);

void	sigint(int sig)
{
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("minishell $> ", 1);
}

void	sigquit(int sig)
{
	
}

void	ignore_signals()
{
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigquit);
}