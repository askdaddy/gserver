//
// Created by Seven on 20/8/5.
//
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/basic_streambuf.hpp>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/system/error_code.hpp>
#include <boost/noncopyable.hpp>
#include <stdio.h>
#include "msg.pb.h"

using namespace boost::asio;

using boost::shared_ptr;
using boost::asio::io_context;
using boost::asio::ip::tcp;
using boost::system::error_code;
using boost::enable_shared_from_this;

using boost::make_shared;
using boost::asio::ip::address;
using boost::asio::buffer;
using boost::asio::basic_streambuf;
using boost::asio::buffer;
using boost::asio::streambuf;


class Server : public boost::noncopyable {
public:
    Server(std::string ip, unsigned short port) :
            io_{make_shared<io_context>()},
            host_{address::from_string(ip), port},
            acceptor_{*io_, host_},
            socket_{*io_} {
        acceptor_.async_accept(socket_,
                               boost::bind(&Server::acceptHandler, this, placeholders::error));
        io_->run();
    }

    ~Server() {
    }

    void acceptHandler(const error_code &e) {
        if (e) {
            std::cout << "accept error!" << std::endl;
            return;
        }

        doRecv();
    }

    void doRecv() {
        streambuf::mutable_buffers_type b_ = recv_buff_.prepare(1048576);
        socket_.async_read_some(buffer(b_),
                                boost::bind(&Server::doRecv, this,
                                            placeholders::bytes_transferred, placeholders::error));
    }

    void doRecv(std::size_t tf_bytes, const error_code &ec) {
        if (!ec) {
            using namespace std;

            recv_buff_.commit(tf_bytes);
            cout << "recv " << tf_bytes << "+" << recv_buff_.size() << endl;

            // 929-2020
            istream reader(&recv_buff_);
            labs_proto::telegram tg;
            bool isParsed = tg.ParseFromIstream(&reader);//tg.ParsePartialFromIstream(&reader);
            if (isParsed) {
                std::cout << tg.code() << " : " << tg.msg() << std::endl;

                // send
                labs_proto::telegram info;
                info.set_code(7);
                info.set_msg("what a wonderful world!");

                boost::asio::streambuf ob;
                std::ostream os(&ob);
                info.SerializeToOstream(&os);
                std::size_t n = socket_.send(ob.data());
                ob.consume(n);
            }

        } else {
            std::cout << ec.message() << std::endl;
            return;
        }

        doRecv();
    }

private:
    shared_ptr <io_context> io_;
    tcp::endpoint host_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;

    streambuf recv_buff_;
};


int main(int argc, const char *argv[]) {
    Server serv("0.0.0.0", 12345);
    return 0;
}