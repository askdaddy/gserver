//
// Created by Seven on 20/7/22.
//

#ifndef G_PACKET_H
#define G_PACKET_H

#include "net.h"

namespace net {
#define PACKET_MAGIC ('Q' << 8 | 'T') //'TQ'
    struct PacketHeader {
        UINT16 magic;
        UINT16 len;
    };

    class Packet {
    public:


    };

    class IPacketHandler {
    public:
        virtual BOOL OnData(Packet &pkt, UINT32 nConnID) = 0;

        virtual BOOL OnClose(UINT32 conn_id) = 0;

        virtual BOOL OnConnect(UINT32 conn_id) = 0;
    };
}
#endif
