//
// Created by Seven on 20/7/30.
//

#ifndef GSERVER_UTLBUFFER_H
#define GSERVER_UTLBUFFER_H

#include "net.h"
#include <boost/asio/buffer.hpp>

namespace net {

    class UtlBuffer {

    public:
        enum Seek_t {
            SEEK_HEAD = 0,
            SEEK_CURRENT,
            SEEK_TAIL
        };

    private:
        UINT32 get_;
        UINT32 put_

        mutable_buffer buff_;

    };
}

//-----------------------------------------------------------------------------
// Where am I reading?
//-----------------------------------------------------------------------------

inline UINT32 UtlBuffer::TellGet() const
{
    return get_;
}


//-----------------------------------------------------------------------------
// What am I reading?
//-----------------------------------------------------------------------------
inline VOID const * UtlBuffer::PeekGet(UINT32 offset) const
{
    return &buff_[m_Get + offset];
}

#endif //GSERVER_UTLBUFFER_H
