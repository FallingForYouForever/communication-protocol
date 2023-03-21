
#include "../Header/pack.h"
#include "../Header/protocol.h"


unsigned short PackBegin (uint8_t *fra)
{
    uint16_t num = 0;
    unsigned int FraIdx = 0;
    /*封装帧头*/
    fra[FraIdx++] = FRAME_HEAD_FIRST;
    fra[FraIdx++] = FRAME_HEAD_SECOND;
    /*预留组号*/
    fra[FraIdx++] = 0x00;
    fra[FraIdx++] = 0x00;
    return 4;
}
unsigned short PackItem (uint8_t *fra,uint8_t ctr,uint8_t addr,uint8_t *data,uint8_t DataLen)
{
    uint8_t i;
    unsigned int FraIdx = 0;
    fra[FraIdx++] = ctr;//添加控制字段
    fra[FraIdx++] = addr;//添加地址字段
    fra[FraIdx++] = DataLen;//添加数据长
    for(i=0;i<DataLen;i++)//添加数据
    {
        fra[FraIdx++] = data[i];
    }
    return DataLen+3;
}
unsigned short PackEnd (uint8_t *fra,uint16_t len)
{
    uint16_t crc16;
    unsigned int FraIdx=len;
    /*封装校验码*/
    crc16 = CRC16_Check(fra,len);
    fra[FraIdx++] = crc16&0xff;
    fra[FraIdx++] = crc16>>8;
    /*封装帧尾*/
    fra[FraIdx++] = FRAME_TAIL;
    return 3;
}
void PackNumCount (uint8_t *fra)
{
    /*封装分组*/
    if(0xff== fra[NumIdx+1]) {
        fra[NumIdx]++;
    }
    fra[NumIdx+1]++;
}
