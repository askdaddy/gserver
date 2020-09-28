//
// Created by Seven on 20/7/6.
//

#ifndef G_NET_H
#define G_NET_H

#include <string>
#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/bind/bind.hpp>
#include "../platform.h"

using namespace boost::asio;

namespace net {
    static const UINT32 MAX_CONNS = 1024;

#define ERROR_RETURN(P) if((P) == FALSE){ return; }
#define ERROR_RETURN_FALSE(P) if((P) == FALSE){return FALSE;}
#define ERROR_RETURN_NULLPTR(P) if((P) == FALSE) {return nullptr;}
}
#endif
