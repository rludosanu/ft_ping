/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolvehost.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/05/16 19:56:03 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern s_env g_env;

int resolvehost(void)
{
	struct addrinfo *res;
	struct addrinfo hints;
	int ret;
	struct in_addr addr;

	if (g_env.tgt == NULL)
		return (-1);

	ret = -1;

	hints.ai_flags = 0;
	hints.ai_family = AF_INET;
	hints.ai_socktype = 0;
	hints.ai_protocol = IPPROTO_ICMP;
	hints.ai_addrlen = 0;
	hints.ai_addr = NULL;
	hints.ai_canonname = NULL;
	hints.ai_next = NULL;

	if (getaddrinfo(g_env.tgt, NULL, &hints, &res) == 0)
	{
		if ((g_env.dst = (struct sockaddr_in *)malloc(sizeof(struct sockaddr_in))))
		{
			memcpy(g_env.dst, res->ai_addr, sizeof(struct sockaddr_in));
			addr = (g_env.dst)->sin_addr;
			inet_ntop(AF_INET, &(addr.s_addr), (char *)&(g_env.sdst), INET_ADDRSTRLEN + 1);
			ret = 0;
		}
		freeaddrinfo(res);
	}

	if (ret == -1)
		printf("ft_ping: unknown host %s\n", g_env.tgt);

	return (ret);
}
