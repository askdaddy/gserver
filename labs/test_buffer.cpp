//
// Created by Seven on 20/8/5.
//
#include <iostream>
#include <boost/make_shared.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/basic_streambuf.hpp>

#include "test_buffer.h"

using namespace boost::asio;

using boost::make_shared;
using boost::asio::ip::address;
using boost::asio::buffer;
using boost::asio::basic_streambuf;

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
    socket_.async_read_some(recv_buff_.prepare(512),
                            boost::bind(&TestBuffer::recvHandler, this,
                                        placeholders::bytes_transferred, placeholders::error));
}

void TestBuffer::recvHandler(std::size_t tf_bytes, const error_code &ec) {
    if (!ec) {
        std::cout << "recv " << tf_bytes << std::endl;

        recv_buff_.commit(tf_bytes);

        std::cout << &recv_buff_ << std::endl;

        std::iostream ios(&recv_buff_);
        std::cout << &ios << std::endl;
    } else {
        std::cout << ec.message() << std::endl;
    }

    doRecv();
}

