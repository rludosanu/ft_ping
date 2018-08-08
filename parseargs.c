/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/09/25 11:39:44 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

extern s_env	g_env;

static int	strisnumber(const char *str)
{
	if (!str || !strlen(str))
		return (0);
	while (*str != '\0')
		if (!isdigit(*str++))
			return (0);
	return (1);
}

int		parseargs(int argc, char **argv)
{
	int			i;
	char		*p;

	if (argc < 2)
		return (infousage(ERR_USG));
	i = 1;
	while (i < argc)
	{
		p = argv[i];
		if (!strcmp(p, "-i"))
		{
			if (g_env.opt_flood == 1)
				return (infousage(ERR_COMPAT));
			else if (!strisnumber(argv[i + 1]) || atoi(argv[i + 1]) < 0)
				return (infousage(ERR_INVARG));
			else
				g_env.opt_delay = atoi(argv[i++ + 1]);
		}
		else if (!strcmp(p, "-t"))
		{
			if (strisnumber(argv[i + 1]) && atoi(argv[i + 1]) > 0)
				g_env.opt_ttl = atoi(argv[i++ + 1]);
			else
				return (infousage(ERR_INVARG));
		}
		else if (*p == '-')
		{
			p++;
			while (*p != '\0')
			{
				if (*p == 'h')
					return (infousage(ERR_USG));
				else if (*p == 'v')
					g_env.opt_verbose = 1;
				else if (*p == 'q')
					g_env.opt_quiet = 1;
				else if (*p == 'f')
				{
					if (g_env.opt_delay == -1)
						g_env.opt_flood = 1;
					else
						return (infousage(ERR_COMPAT));
				}
				else
					return (infousage(ERR_INVOPT));
				p++;
			}
		}
		else
		{
			if (strisnumber(argv[i]))
				return (infousage(ERR_INVARG));
			if (g_env.opt_delay == -1)
				g_env.opt_delay = 1;
			g_env.tgt = argv[i];
			return (0);
		}
		i++;
	}
	return (infousage(ERR_USG));
}
