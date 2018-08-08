/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenviron.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/05/16 19:56:03 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern s_env	g_env;

void			setenviron(void)
{
	g_env.flg = 0;
	g_env.id = getpid();
	g_env.seq = 1;
	g_env.tgt = NULL;
	g_env.dst = NULL;
	memset(&(g_env.sdst), 0, INET_ADDRSTRLEN + 1);
	g_env.n_transmitted = 0;
	g_env.n_received = 0;
	g_env.n_errors = 0;
	g_env.rtt_min = 0;
	g_env.rtt_max = 0;
	g_env.rtt_sum = 0;
	g_env.opt_reuseaddr = 1;
	g_env.opt_verbose = 0;
	g_env.opt_delay = -1;
	g_env.opt_ttl = 64;
	g_env.opt_quiet = 0;
	g_env.opt_flood = 0;
}

int				unsetenviron(void)
{
	close(g_env.sock);

	if (g_env.dst)
		free(g_env.dst);

	return (0);
}
