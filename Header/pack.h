#ifndef _PACK_H_
#define _PACK_H_
#include "public.h"

#define NumIdx 2
#define   PACK_BEGIN(fra, len)\
    {\
       (len) += PackBegin(fra);

#define PACKITEM(ctr, addr, data, datalen)\
	(len) += PackItem(fra + (len), ctr, addr, data, datalen);\
	PackNumCount(fra);

#define  PACK_END()\
	(len) += PackEnd(fra, (len));\
    }

unsigned short PackBegin (uint8_t *fra);
unsigned short PackItem (uint8_t *fra,uint8_t ctr,uint8_t addr,uint8_t *data,uint8_t DataLen);
unsigned short PackEnd (uint8_t *fra,uint16_t len);
void PackNumCount (uint8_t *fra);
#endif