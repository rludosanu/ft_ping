/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_packet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/05/16 19:56:03 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern s_env			g_env;

/*
** Sends out an ICMP packet + payload.
** Payload contains a timeval structure defining the timestamp of the send.
*/

void					send_packet(void)
{
	struct icmp 		*icmp;
	char				*packet;
	size_t				packet_size;
	size_t				payload_size;
	struct sockaddr_in	sin;
	struct timeval		tv_out;

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = g_env.dst->sin_addr.s_addr;
	ft_memset(&(sin.sin_zero), 0, sizeof(sin.sin_zero));

	payload_size = sizeof(struct timeval);
	packet_size = sizeof(struct icmp) + payload_size;
	if (!(packet = (char *)malloc(packet_size)))
		return ;

	ft_memset(packet, 0, packet_size);
	gettimeofday(&tv_out, NULL);
	ft_memcpy(packet + sizeof(struct icmp), &tv_out, sizeof(struct timeval));

	icmp = (struct icmp *)packet;
	icmp->icmp_type = 8;
	icmp->icmp_code = 0;
	icmp->icmp_cksum = 0;
	icmp->icmp_id = g_env.id;
	icmp->icmp_seq = g_env.seq;
	icmp->icmp_cksum = checksum((unsigned short *)icmp, sizeof(struct icmp) + payload_size);

	if (sendto(g_env.sock, packet, packet_size, 0, (struct sockaddr *)&sin, sizeof(sin)) > 0)
	{
		g_env.seq += 1;
		g_env.n_transmitted += 1;
	}

	free(packet);
}
