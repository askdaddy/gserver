//
// Created by Seven on 20/8/5.
//
#include <iostream>
#include <boost/make_shared.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/basic_streambuf.hpp>
#include "test_buffer.h"
#include <stdio.h>

using namespace boost::asio;

using boost::make_shared;
using boost::asio::ip::address;
using boost::asio::buffer;
using boost::asio::basic_streambuf;
using boost::asio::buffer;
using boost::asio::streambuf;

TestBuffer::TestBuffer(std::string ip, unsigned short port) :
        io_{make_shared<io_context>()},
        host_{address::from_string(ip), port},
        acceptor_{*io_, host_},
        socket_{*io_} {

    acceptor_.async_accept(socket_,
                           boost::bind(&TestBuffer::acceptHandler, this, placeholders::error));
    io_->run();
}

TestBuffer::~TestBuffer() {

}


void TestBuffer::acceptHandler(const error_code &e) {
    if (e) {
        std::cout << "accept error!" << std::endl;
        return;
    }

    doRecv();
}

void TestBuffer::doRecv() {
    streambuf::mutable_buffers_type b_ = recv_buff_.prepare(256);
    socket_.async_read_some(buffer(b_),
                            boost::bind(&TestBuffer::recvHandler, this,
                                        placeholders::bytes_transferred, placeholders::error));
}

void TestBuffer::recvHandler(std::size_t tf_bytes, const error_code &ec) {
    if (!ec) {
        std::cout << "recv " << tf_bytes << std::endl;
        recv_buff_.commit(tf_bytes);

//        auto bufs = recv_buff_.data();

//        std::istream is(&recv_buff_);
//        std::string s;
//        is >> s;
        char cs[6];
        char* cs_pos = cs;

        recv_buff_.sgetn(cs, sizeof cs);
        recv_buff_.consume(sizeof cs);

        UINT16 mg;
        UINT32 le;
        mg = *(UINT16 *) cs_pos;

        cs_pos += sizeof(UINT16);

        le = *(UINT32 *) cs_pos;


        std::cout << le << std::endl;



        char ms[64];
        recv_buff_.sgetn(ms,le);
        recv_buff_.consume(le);



//        std::cout << recv_buff_.size() << ": " << ms << std::endl;

        std::ostream os(&tran_buff_);
        os << "got msg.: " << ms << std::endl;

        socket_.send(tran_buff_.data());

    } else {
        std::cout << ec.message() << std::endl;
        return;
    }

    doRecv();
}

