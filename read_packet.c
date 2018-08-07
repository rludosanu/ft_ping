/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_packet.c                                      :+:      :+:    :+:   */
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
** Reads an incoming ICMP packet response
*/

void					read_packet(void)
{
	struct iovec		iov;
	struct msghdr		msg;
	char				buf[100];
	char 				*ptr;
	struct timeval		*tv_out;
	struct timeval		tv_in;
	struct ip			*ip;
	struct icmp			*icmp;
	double				tv_delta;
	int 				n;

	ft_memset(&iov, 0, sizeof(iov));
	ft_memset(&msg, 0, sizeof(msg));

	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	iov.iov_base = buf;
	iov.iov_len = sizeof(buf);
	msg.msg_iov = &iov;
	msg.msg_iovlen = 1;
	msg.msg_control = NULL;
	msg.msg_controllen = 0;
	msg.msg_flags = 0;

	if ((n = recvmsg(g_env.sock, &msg, 0)) > 0)
	{
		ptr = (char *)msg.msg_iov->iov_base;
		ip = (struct ip *)ptr;
		icmp = (struct icmp *)(ptr + (ip->ip_hl * 4));

		gettimeofday(&tv_in, NULL);
		tv_out = (struct timeval *)(icmp + 1);
		tv_delta = timevaldiff(tv_out, &tv_in);

		if (icmp->icmp_type != 8)
		{
			if (g_env.opt_quiet == 0)
			{
				if (icmp->icmp_type != 0)
				{
					if (g_env.opt_verbose == 1)
						printf("From %s: icmp_type=%d icmp_code=%d\n", g_env.sdst, icmp->icmp_type, icmp->icmp_code);
				}
				else
				{
					printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.4f ms\n", n, g_env.sdst, icmp->icmp_seq, ip->ip_ttl, tv_delta);
				}
			}

			if (icmp->icmp_type == 0)
			{
				g_env.rtt_sum += tv_delta;
				if (tv_delta > g_env.rtt_max)
					g_env.rtt_max = tv_delta;
				if (g_env.rtt_min == 0)
					g_env.rtt_min = tv_delta;
				else if (tv_delta < g_env.rtt_min)
					g_env.rtt_min = tv_delta;
				g_env.n_received += 1;
			}
			else
				g_env.n_errors += 1;
		}
	}
}
