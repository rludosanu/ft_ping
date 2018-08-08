/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rludosan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 17:33:02 by rludosan          #+#    #+#             */
/*   Updated: 2017/05/16 19:56:03 by rludosan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <ctype.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <netinet/in.h>
# include <netinet/in_systm.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>
# include <sys/time.h>

# define ERR_USG 1
# define ERR_INVOPT 2
# define ERR_INVARG 3
# define ERR_COMPAT 4

/* Global environ */
typedef struct t_env
{
	int sock;
	int id;
	int seq;
	char *tgt;
	struct sockaddr_in *dst;
	char sdst[INET_ADDRSTRLEN + 1];
	int flg;
	int n_transmitted;
	int n_received;
	int n_errors;
	double rtt_min;
	double rtt_max;
	double rtt_sum;
	struct timeval tv_start;
	struct timeval tv_end;
	int opt_reuseaddr;
	int opt_verbose;
	int opt_delay;
	int opt_ttl;
	int opt_quiet;
	int opt_flood;
} s_env;

/* Command line arguments parser */
int parseargs(int argc, char **argv);

/* Internet checksum */
unsigned short checksum(unsigned short *ptr, int nbytes);

/* Error msg handler */
int infousage(int e);

/* Time */
double timevaldiff(struct timeval *tv_1, struct timeval *tv_2);

/* Environ */
void setenviron(void);
int unsetenviron(void);

/* IMCP Packets */
void send_packet(void);
void read_packet(void);

/* Signals */
void sighdl_pkt(int sig);
void sighdl_stat(int sig);

/* Host */
int resolvehost(void);

#endif
