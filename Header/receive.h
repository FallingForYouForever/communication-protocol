#ifndef RECEIVE_H
#define RECEIVE_H

#include "string.h"
#include "protocol.h"
#include "public.h"
enum STEP{
            IDLE_STATUS=0,
            HEADER_TWO_RECEIVING,
            NUM_ONE_RECEIVING,
            NUM_TWO_RECEIVING,
            CTR_RECEIVING,
            ADDR_RECEIVING,
            LEN_RECEIVING,
            DATA_RECEIVING,
            CHECK_ONE,
            CHECK_TWO,
            TAIL_REEIVING
};

#define INIT_VALUE 0

void Receive (uint8_t bytedata);
#endif
