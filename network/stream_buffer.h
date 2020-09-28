//
// Created by Seven on 2020/9/23.
//

#ifndef GSERVER_STREAM_BUFFER_H
#define GSERVER_STREAM_BUFFER_H


#include "../platform.h"

class StreamBuffer {
public:
    StreamBuffer();
    virtual ~StreamBuffer();

    CHAR GetChar();

    // Where am I writing (put)/reading (get)?
    UINT32 TellPut() const;
    UINT32 TellGet() const;

private:
    CHAR buff_;
    UINT32 get_;
    UINT32 put_;
};


#endif //GSERVER_STREAM_BUFFER_H
