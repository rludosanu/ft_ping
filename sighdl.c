/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighdl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/09/25 11:33:22 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern s_env	g_env;

void            sighdl_pkt(int sig)
{
	(void)sig;
	send_packet();
	alarm(g_env.opt_delay);
}

/*
** Prints out the ping recap statistics on a Ctrl+C (SIGINT)
*/

void            sighdl_stat(int sig)
{
	(void)sig;

	gettimeofday(&(g_env.tv_end), NULL);

	printf("\n--- %s ping statistics ---\n", g_env.tgt);
	printf("%d packets transmitted, ", g_env.n_transmitted);
	printf("%d received, ", g_env.n_received);
	if (g_env.n_errors != 0)
		printf("+%d errors, ", g_env.n_errors);
	printf("%d%% packet loss, ", 100 - ((g_env.n_received * 100) / g_env.n_transmitted));
	printf("time %.fms\n", timevaldiff(&(g_env.tv_start), &(g_env.tv_end)));
	if (g_env.n_received != 0)
		printf("rtt min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", g_env.rtt_min, g_env.rtt_sum / g_env.n_received, g_env.rtt_max, g_env.rtt_max - g_env.rtt_min);

	unsetenviron();
	exit(0);
}
