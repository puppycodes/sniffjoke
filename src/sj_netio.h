/*
 *   SniffJoke is a software able to confuse the Internet traffic analysis,
 *   developed with the aim to improve digital privacy in communications and
 *   to show and test some securiy weakness in traffic analysis software.
 *   
 *   Copyright (C) 2010 vecna <vecna@delirandom.net>
 *                      evilaliv3 <giovanni.pellerano@evilaliv3.org>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SJ_NETIO_H
#define SJ_NETIO_H

#include "sj_defines.h"
#include "sj_conf.h"
#include "sj_tcptrack.h"

#include <poll.h>

#include <netpacket/packet.h>

#define MTU             1500
#define BURSTSIZE       10

class NetIO {
private:
	/* 
	 * these data are required for handle 
	 * tunnel/ethernet man in the middle
	 */
	struct sockaddr_ll send_ll;
	struct sj_config *runcopy;

	/* tunfd/netfd: file descriptor for I/O purpose */
	int tunfd;
	int netfd;

        /* poll variables, two file descriptors */
        struct pollfd fds[2];

	TCPTrack *conntrack;

	unsigned char pktbuf[MTU];
	int size;
	Packet *pkt;

	bool networkdown_condition;

public:

	/* networkdown_condition express if the network is down and sniffjoke must be interrupted 
	 *	   --- but not killed!
	 */

	NetIO(SjConf*);
	~NetIO(void);
	void prepare_conntrack(TCPTrack*);
	void network_io(void);
	void queue_flush(void);
	bool is_network_down(void);
	void set_running(bool);
};

#endif /* SJ_NETIO_H */