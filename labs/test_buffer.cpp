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
#include "msg.pb.h"

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
                            boost::bind(&TestBuffer::doRecv, this,
                                        placeholders::bytes_transferred, placeholders::error));
}

void TestBuffer::doRecv(std::size_t tf_bytes, const error_code &ec) {
    if (!ec) {
        std::cout << "recv " << tf_bytes << std::endl;
        recv_buff_.commit(tf_bytes);

        // 929-2020
        std::istream reader(&recv_buff_);
        labs_proto::telegram tg;
        tg.ParsePartialFromIstream(&reader);

        std::cout << tg.code() << " : " << tg.msg() << std::endl;
//        google::protobuf::io::* raw_input;//(&reader);

        // --end 929


        // send --
//        std::ostream os(&tran_buff_);
//        os << "got msg.: "<< tg.code() << std::endl;
//        labs_proto::telegram* tel;
//        tel->set_code(12);
//        socket_.send(tran_buff_.data());

    } else {
        std::cout << ec.message() << std::endl;
        return;
    }

    doRecv();
}

