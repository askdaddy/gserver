//
// Created by Seven on 20/7/6.
//

#include "server_net.h"
#include <boost/asio.hpp>

using namespace net;
using namespace boost::asio;

ServerNet::ServerNet(void) {}

ServerNet::~ServerNet(void) {}

VOID ServerNet::Start(std::string ipv4, UINT16 port) {
    ConnectionMgr::GetInstancePtr()->InitConnections(io_);

    if (ipv4.empty() || ipv4.length() < 4) {
        ipv4 = "0.0.0.0";
    }

    ip::tcp::endpoint addr(ip::address_v4::from_string(ipv4), port);

    acceptor_ = new ip::tcp::acceptor(io_, addr, TRUE);

    WaitForConnect();

//    work_thread_ = new boost::thread(boost::bind(&boost::asio::io_context::run, &io_));

    io_.run();
}

BOOL ServerNet::WaitForConnect() {
    Connection_ptr conn = ConnectionMgr::GetInstancePtr()->AlloConnection();
    ERROR_RETURN_FALSE(conn != nullptr);

    acceptor_->async_accept(conn->GetSocket(),
                            boost::bind(&ServerNet::HandleAccept, this, conn, placeholders::error));

    return TRUE;
}

VOID ServerNet::HandleAccept(Connection_ptr &conn, const boost::system::error_code &e) {
    if (e) {
        conn->Close();
        return;
    }

    conn->DoReceive();

    WaitForConnect();
}


VOID ServerNet::Shutdown() {

    io_.stop();

    acceptor_->close();

    delete acceptor_;

//    work_thread_->join();

//    delete work_thread_;

    ConnectionMgr::GetInstancePtr()->DestroyConnections();
}