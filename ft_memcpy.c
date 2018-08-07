/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:57:00 by rludosan          #+#    #+#             */
/*   Updated: 2015/11/28 16:04:49 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*c1;
	const char	*c2;

	c1 = (char *)dst;
	c2 = (const char *)src;
	while (n--)
		*c1++ = *c2++;
	return (dst);
}
