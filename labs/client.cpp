//
// Created by Seven on 2021/3/24.
//
#include <iostream>
#include <boost/make_shared.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/asio/basic_streambuf.hpp>
#include <boost/system/error_code.hpp>
#include <stdio.h>
#include "msg.pb.h"

using namespace boost::asio;

using boost::asio::io_context;
using boost::asio::ip::tcp;
using boost::shared_ptr;
using boost::system::error_code;
using boost::make_shared;
using boost::asio::ip::address;
using boost::asio::buffer;
using boost::asio::basic_streambuf;
using boost::asio::buffer;
using boost::asio::streambuf;

class Client : public boost::noncopyable {
public:
    Client(std::string addr, std::string port) :
            io_{make_shared<io_context>()},
            socket_{*io_}, resolver_{*io_} {


        resolver_.async_resolve(tcp::v4(), addr, port,
                                boost::bind(&Client::on_resolve, this,
                                            placeholders::error, placeholders::results));
        io_->run();
    }

    ~Client() {}

    void on_resolve(const error_code &ec,
                    tcp::resolver::results_type endpoints) {
        if (ec) {
            std::cerr << "Resolve: " << ec.message() << std::endl;
        } else {
            std::cerr << "Do connect "  << std::endl;
            async_connect(socket_, endpoints,
                          boost::bind(&Client::on_connected, this,
                                      placeholders::error,
                                      placeholders::endpoint));
        }
    }


    void on_connected(const error_code ec, const tcp::endpoint endpoint) {
        if (ec) {
            std::cout << "Connect failed: " << ec.message() << std::endl;
            socket_.close();
        } else {
//            DoWrite();
            std::cout << "Do write " << std::endl;
            // send
            labs_proto::telegram info;
            info.set_code(996);
            info.set_msg("Hello world!");

            boost::asio::streambuf ob;
            std::ostream os(&ob);
            info.SerializeToOstream(&os);
            std::size_t n = socket_.send(ob.data());
            ob.consume(n);
        }
    }

private:
    shared_ptr <io_context> io_;
    tcp::socket socket_;
    tcp::resolver resolver_;
    tcp::endpoint host_;
};


int main(int argc, const char *argv[]) {
    Client client("localhost", "12345");
    return 0;
}