/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infousage.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/05/16 19:56:03 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int		infousage(int e)
{
	if (e == ERR_USG)
		printf("Usage: ./ft_ping [-hvqf] [-i interval] [-t ttl] destination\n");
	else if (e == ERR_INVOPT)
		printf("ft_ping: unknown option\n");
	else if (e == ERR_INVARG)
		printf("ft_ping: invalid argument\n");
	else if (e == ERR_COMPAT)
		printf("ft_ping: -i and -f incompatible options\n");
	return (-1);
}
