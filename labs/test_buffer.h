//
// Created by Seven on 20/8/5.
//

#ifndef GSERVER_TEST_BUFFER_H
#define GSERVER_TEST_BUFFER_H

#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/system/error_code.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio/basic_streambuf.hpp>

using boost::shared_ptr;
using boost::asio::io_context;
using boost::asio::ip::tcp;
using boost::system::error_code;
using boost::enable_shared_from_this;
using boost::asio::streambuf;

class TestBuffer : public boost::noncopyable {
public:
    TestBuffer(std::string ip,
               unsigned short port);

    ~TestBuffer();


    void acceptHandler(const error_code &e);

    void doRecv();

    void recvHandler(std::size_t tf_bytes, const error_code &ec);


private:
    shared_ptr<io_context> io_;
    tcp::endpoint host_;
    tcp::acceptor acceptor_;
    tcp::socket socket_;

    char recv_buff_[256];
    char* recv_pos;

};


#endif //GSERVER_TEST_BUFFER_H
