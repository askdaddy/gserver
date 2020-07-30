//
// Created by Seven on 20/7/6.
//

#ifndef G_CONNECTION_H
#define G_CONNECTION_H

#include <deque>
#include <mutex>
#include "net.h"
#include "packet.h"

using namespace boost::asio;

namespace net {

#define RECV_BUF_SIZE               8192
    typedef std::deque<mutable_buffer> BufferQueue;

    class Connection {
    public:
        explicit Connection(io_context &io);

        virtual ~Connection();

    public:
        virtual VOID Close();

        virtual BOOL IsValid();

        VOID SetId(UINT32 id);

        UINT32 GetId() const;

        VOID SetHandler(IPacketHandler *hdl);

        ip::tcp::socket &GetSocket();

        VOID DoReceive();

        Connection *GetNext();

        VOID SetNext(Connection *c);

        VOID Reset();

    private:
        VOID OnData(const boost::system::error_code &e, std::size_t data_len);

    private:
        UINT32 id_;
        ip::tcp::socket socket_;

        BOOL connected_;

        UINT32 data_len_;
        CHAR recv_buff_[RECV_BUF_SIZE];
        CHAR *buff_pos_;

        IPacketHandler *handler_;

        BufferQueue send_list_;

    private:
        Connection *next_;
    };


    class ConnectionMgr {
        ConnectionMgr();

        ~ConnectionMgr();

    public:
        static ConnectionMgr *GetInstancePtr() {
            static ConnectionMgr mgr;
            return &mgr;
        }

        BOOL InitConnections(io_context &io);

        Connection *AlloConnection();

        VOID DestroyConnections();

        Connection *GetConnection(UINT32 id);

        BOOL DelConnection(UINT32 id);

        BOOL DelConnection(Connection *conn);

    private:
        std::vector<Connection *> conn_list_;
        Connection *free_conn_head_;
        Connection *free_conn_tail_;
        std::mutex conn_list_mutex_;
    };
}


#endif
