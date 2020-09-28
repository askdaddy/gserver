//
// Created by Seven on 20/7/6.
//

#include "connection.h"
#include <iostream>

using namespace net;

Connection::Connection(io_context &io)
        : socket_(io) {
    handler_ = NULL_PTR;
    connected_ = FALSE;

    id_ = 0;
    ResetBuff();
}

Connection::~Connection() {
    ResetBuff();
    handler_ = NULL_PTR;
    id_ = 0;
}

Connection_ptr Connection::GetNext() {
    return next_;
}

VOID Connection::SetNext(Connection_ptr c) {
    next_ = c;
}

ip::tcp::socket &Connection::GetSocket() {
    return socket_;
}

VOID Connection::SetId(UINT32 id) {
    ERROR_RETURN(0 != id);
    ERROR_RETURN(!connected_);

    id_ = id;
}

UINT32 Connection::GetId() const {
    return id_;
}

VOID Connection::SetHandler(PacketHandler_ptr hdl) {
    ERROR_RETURN(NULL_PTR != hdl);
    handler_ = hdl;
}

BOOL Connection::IsValid() {
    return connected_ && socket_.is_open();
}

VOID Connection::Close() {
    socket_.shutdown(socket_base::shutdown_receive);
    socket_.shutdown(socket_base::shutdown_send);
    socket_.close();

    if (handler_ != nullptr) {
        handler_->OnClose(GetId());
    }
    connected_ = false;
}

VOID Connection::DoReceive() {
    socket_.async_read_some(buffer(recv_buff_ + recv_len_, RECV_BUF_SIZE - recv_len_),
                            boost::bind(&Connection::OnData, this, placeholders::error,
                                        placeholders::bytes_transferred));

}

VOID Connection::OnData(const boost::system::error_code &e, std::size_t data_len) {
    if (!e) {
        // Handle recv
        recv_len_ += data_len;

        ParseBuffer();
        DoReceive();

        return;
    }

    Close();
}

VOID Connection::ParseBuffer() {
    UINT32 header_len = sizeof(PacketHeader);
    if (recv_len_ < header_len) {
        return;
    }

    PacketHeader *pHeader = (PacketHeader *) recv_buff_pos_;
    if (CheckHeader(recv_buff_pos_)) {

        return;
    }

    ERROR_RETURN(pHeader->len != 0);

    UINT32 body_len = pHeader->len;

    if ((header_len + body_len) < recv_len_) {

    }

}

VOID Connection::Reset() {
    connected_ = FALSE;
    ResetBuff();
}

VOID Connection::ResetBuff() {
    recv_buff_pos_ = recv_buff_;
    recv_len_ = 0;
    data_buff_pos_ = data_buff_;
    data_len_ = 0;
}


BOOL Connection::CheckHeader(CHAR *pBuff) {
    PacketHeader *pHeader = (PacketHeader *) pBuff;
    ERROR_RETURN_FALSE(pHeader->magic == PACKET_MAGIC);
    ERROR_RETURN_FALSE(pHeader->len < PACKET_PAYLOAD_MAX_LEN);
    return TRUE;
}

// ----------------------------------------------------------------------- \\

ConnectionMgr::ConnectionMgr() {
    free_conn_head_ = nullptr;
    free_conn_tail_ = nullptr;
}

ConnectionMgr::~ConnectionMgr() {
    DestroyConnections();

    free_conn_head_ = nullptr;
    free_conn_tail_ = nullptr;
}

BOOL ConnectionMgr::InitConnections(io_context &io) {
    conn_list_.assign(MAX_CONNS, NULL_PTR);
    for (uint32_t i = 0; i < MAX_CONNS; ++i) {
        Connection_ptr conn(new Connection(io));
        conn_list_[i] = conn;
        conn->SetId(i + 1);

        if (free_conn_head_ == NULL_PTR) {
            free_conn_head_ = conn;

            conn->SetNext(NULL_PTR);

            free_conn_tail_ = conn;
        } else {
            free_conn_tail_->SetNext(conn);
            free_conn_tail_ = conn;
            free_conn_tail_->SetNext(nullptr);
        }
    }

    return TRUE;
}

Connection_ptr ConnectionMgr::AlloConnection() {
    Connection_ptr conn;
    conn_list_mutex_.lock();

    if (!free_conn_head_) {
        conn_list_mutex_.unlock();
        return NULL_PTR;
    }

    if (free_conn_head_ == free_conn_tail_) {
        conn = free_conn_head_;
        free_conn_tail_ = free_conn_head_ = NULL_PTR;
    } else {
        conn = free_conn_head_;
        free_conn_head_ = conn->GetNext();
        conn->SetNext(NULL_PTR);
    }
    conn_list_mutex_.unlock();

    return conn;
}

Connection_ptr ConnectionMgr::GetConnection(UINT32 id) {
    ERROR_RETURN_NULLPTR(id != 0);

    UINT32 mod = id % conn_list_.size();

    Connection_ptr &conn = conn_list_.at(mod == 0 ? (conn_list_.size() - 1) : (mod - 1));

    ERROR_RETURN_NULLPTR (conn->GetId() != id);

    return conn;
}

BOOL ConnectionMgr::DelConnection(Connection_ptr conn) {
    ERROR_RETURN_FALSE(conn != nullptr);

    conn_list_mutex_.lock();

    if (free_conn_tail_ == NULL_PTR) {
        ERROR_RETURN_FALSE(free_conn_head_ == NULL_PTR);

        free_conn_tail_ = free_conn_head_ = conn;
    } else {
        free_conn_tail_->SetNext(conn);
        free_conn_tail_ = conn;
        free_conn_tail_->SetNext(NULL_PTR);
    }

    conn_list_mutex_.unlock();
    UINT32 id = conn->GetId();
    conn->Reset();
    id += (UINT32) conn_list_.size();
    conn->SetId(id);

    return TRUE;
}

BOOL ConnectionMgr::DelConnection(UINT32 id) {
    ERROR_RETURN_FALSE(id != 0);
    Connection_ptr conn = GetConnection(id);
    ERROR_RETURN_FALSE(conn != NULL_PTR);

    return DelConnection(conn);
}


VOID ConnectionMgr::DestroyConnections() {
    Connection_ptr conn = NULL_PTR;
    for (size_t i = 0; i < conn_list_.size(); ++i) {
        conn = conn_list_.at(i);
        conn->Close();
        conn = NULL_PTR; // Destroy
    }

    conn_list_.clear();
}


