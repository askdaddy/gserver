//
// Created by Seven on 20/7/22.
//

#ifndef G_PACKET_H
#define G_PACKET_H

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include "net.h"

namespace net {

#define PACKET_MAGIC ('Q' << 8 | 'T') //'TQ'
#define PACKET_PAYLOAD_MAX_LEN  10240

    struct PacketHeader {
        UINT16 magic;
        UINT16 len;
    };

    class Packet {


    };

    class PacketHandler : public boost::enable_shared_from_this<PacketHandler> {
    public:
        virtual BOOL OnData(Packet &pkt, UINT32 nConnID) = 0;

        virtual BOOL OnClose(UINT32 conn_id) = 0;

        virtual BOOL OnConnect(UINT32 conn_id) = 0;
    };

    using PacketHandler_ptr = boost::shared_ptr<PacketHandler>;
}
#endif
