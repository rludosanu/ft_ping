/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/05/16 19:56:03 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

s_env	g_env;

int		main(int argc, char **argv)
{
	// Set base environ
	setenviron();

	// Parse CLI arguments
	if (parseargs(argc, argv) == -1)
		return (unsetenviron());

	// Resolve host
	if (resolvehost() == -1)
		return (unsetenviron());

	// Create ICMP socket
	if ((g_env.sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
		return (unsetenviron());

	// Add socket options
	setsockopt(g_env.sock, SOL_SOCKET, SO_REUSEADDR, &(g_env.opt_reuseaddr), sizeof(g_env.opt_reuseaddr));
	setsockopt(g_env.sock, IPPROTO_IP, IP_TTL, &(g_env.opt_ttl), sizeof(g_env.opt_ttl));

	// Print the first ping info line
	gettimeofday(&(g_env.tv_start), NULL);
	printf("PING %s (%s)\n", g_env.tgt, g_env.sdst);

	// Signal handler for statistics
	signal(SIGINT, sighdl_stat);
	if (g_env.opt_delay != 0 && g_env.opt_flood != 1)
	{
		// Signal handler for alarm
		signal(SIGALRM, sighdl_pkt);
		// Start alarm
		alarm(g_env.opt_delay);
	}


	// Send the first packet
	send_packet();

	// Start the main loop
	while (1)
	{
		read_packet();
		if (g_env.opt_delay == 0 || g_env.opt_flood == 1)
			send_packet();
	}

	return (unsetenviron());
}
