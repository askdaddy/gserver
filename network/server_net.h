//
// Created by Seven on 20/7/6.
//

#ifndef G_SERVER_NET_H
#define G_SERVER_NET_H

#include "net.h"

#include "connection.h"

//#include <boost/thread.hpp>

namespace net {

    class ServerNet {
        ServerNet(void);

        virtual ~ServerNet(void);

    public:
        static ServerNet *GetInstancePtr() {
            static ServerNet net_mgr_;
            return &net_mgr_;
        }

    public:
        virtual VOID Start(std::string ipv4, UINT16 port);

        VOID Shutdown();

        VOID HandleAccept(Connection *conn, const boost::system::error_code &e);

        BOOL WaitForConnect();

    private:

        boost::asio::io_context io_;
        boost::asio::ip::tcp::acceptor *acceptor_;
//        boost::thread *work_thread_;
    };
}


#endif
