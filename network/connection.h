//
// Created by Seven on 20/7/6.
//

#ifndef G_CONNECTION_H
#define G_CONNECTION_H

#include <deque>
#include <mutex>
#include "net.h"
#include "packet.h"
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>

#define RECV_BUF_SIZE               512
using namespace boost::asio;

namespace net {

    class Connection;

    using Connection_ptr = boost::shared_ptr<Connection>;

    class Connection : public boost::enable_shared_from_this<Connection>, private boost::noncopyable {
    public:
        explicit Connection(io_context &io);

        virtual ~Connection();

    public:
        virtual VOID Close();

        virtual BOOL IsValid();

        VOID SetId(UINT32 id);

        UINT32 GetId() const;

        VOID SetHandler(PacketHandler_ptr hdl);

        ip::tcp::socket &GetSocket();

        VOID DoReceive();

        Connection_ptr GetNext();

        VOID SetNext(Connection_ptr c);

        VOID Reset();

    private:
        VOID OnData(const boost::system::error_code &e, std::size_t data_len);

        BOOL HandleRecv(UINT32 len);
        BOOL CheckHeader(CHAR* packet_buff);

    private:
        UINT32 id_;
        ip::tcp::socket socket_;

        BOOL connected_;

        UINT32 data_len_;
        CHAR recv_buff_[RECV_BUF_SIZE];
        CHAR *buff_pos_;

        PacketHandler_ptr handler_;

//        BufferQueue send_list_;


        Connection_ptr next_;
    };


//* ------------------------------------------------------ *\\

    class ConnectionMgr {
        ConnectionMgr();

        ~ConnectionMgr();

    public:
        static ConnectionMgr *GetInstancePtr() {
            static ConnectionMgr mgr;
            return &mgr;
        }

        BOOL InitConnections(io_context &io);

        Connection_ptr AlloConnection();

        VOID DestroyConnections();

        Connection_ptr GetConnection(UINT32 id);

        BOOL DelConnection(UINT32 id);

        BOOL DelConnection(Connection_ptr conn);




    private:

        std::vector<Connection_ptr> conn_list_;
        Connection_ptr free_conn_head_;
        Connection_ptr free_conn_tail_;
        std::mutex conn_list_mutex_;
    };
}


#endif
