

#include "../Header/pack.h"
#include "../Header/protocol.h"
#include "../Header/receive.h"
#include "../Header/unpack.h"


void resetData(void);

uint8_t step = IDLE_STATUS; // 状态变量初始化为0
uint8_t idx = INIT_VALUE, ctr = INIT_VALUE, addr = INIT_VALUE, *data_ptr = NULL,
               *unpack_ptr = NULL, counts = INIT_VALUE, NumFirst = INIT_VALUE,
               NumSecond = INIT_VALUE, buf[MAX_SIZE], dataLen = INIT_VALUE;
uint16_t crc16 = INIT_VALUE, num = INIT_VALUE;
uint32_t len = INIT_VALUE ;

//接收数据
void  Receive (uint8_t bytedata)
{
    switch(step)//进行数据接收 状态机
    {
        case IDLE_STATUS://接收帧头1状态
        {
            if (bytedata == FRAME_HEAD_FIRST) {
                step = HEADER_TWO_RECEIVING;
                idx = 0;
                buf[idx++] = bytedata;
            }
            break;
        }
        case HEADER_TWO_RECEIVING://接收帧头2状态
        {
            if(bytedata== FRAME_HEAD_SECOND)
            {
                step=NUM_ONE_RECEIVING;
                buf[idx++] = bytedata;
            }
            else if(bytedata== FRAME_HEAD_FIRST)
            {
                step = HEADER_TWO_RECEIVING;
            }
            else
            {
                step = IDLE_STATUS;
            }
            break;
        }
        case NUM_ONE_RECEIVING://接收数据分组1字节状态
        {
            step=NUM_TWO_RECEIVING;
            buf[idx++] = bytedata;
            NumFirst= bytedata;
            break;
        }
        case NUM_TWO_RECEIVING://接收数据分组2字节状态
        {
            step=CTR_RECEIVING;
            buf[idx++] = bytedata;
            unpack_ptr=&buf[idx];//解包指针,解析起始位置
            NumSecond = bytedata;
            num = (NumFirst<<8) | NumSecond;
            if(num <= 0)
            {
                step = IDLE_STATUS;//数据分组长度为0则跳过数据接收状态
            }
            break;
        }
        case CTR_RECEIVING: // 接收控制字节状态
        {
            step=ADDR_RECEIVING;
            len++;
            counts++;//分组序数
            buf[idx++] = bytedata;
            ctr = bytedata;
            break;
        }
        case ADDR_RECEIVING://接收目的地址字节状态
        {
            step=LEN_RECEIVING;
            len++;
            buf[idx++] = bytedata;
            addr = bytedata;
            break;
        }
        case LEN_RECEIVING:
        {
            step = DATA_RECEIVING;
            len++;
            buf[idx++] = bytedata;
            data_ptr = &buf[idx];//记录数据指针首地址
            dataLen = bytedata;
            break;
        }
        case DATA_RECEIVING: // 接收num字节数据状态 判断是否接收完num组数据
        {
            buf[idx++] = bytedata;
            len++;
            if(data_ptr + dataLen == &buf[idx]){
                if(counts==num){
                    step = CHECK_ONE;
                }else if(counts<num){
                    step = CTR_RECEIVING;
                }
            }
            break;
        }
        case  CHECK_ONE://接收crc16校验高8位字节
        {
            crc16 = bytedata;
            step = CHECK_TWO;
            break;
        }
        case CHECK_TWO://接收crc16校验低8位字节
        {
            crc16 += (bytedata<<8);
            if(crc16 == CRC16_Check(buf,idx))//校验正确进入下一状态
            {
                step=TAIL_REEIVING;
            }
            else if(bytedata == FRAME_HEAD_FIRST)
            {
                step = HEADER_TWO_RECEIVING;
            }
            else
            {
                step = IDLE_STATUS;
                resetData();
            }
            break;
        }
        case TAIL_REEIVING: // 接收帧尾
        {
            if(bytedata==FRAME_TAIL)//帧尾接收正确
            {

                Unpack(unpack_ptr,len);
                resetData();
            }
            else if(bytedata == FRAME_HEAD_FIRST)
            {
                step = HEADER_TWO_RECEIVING;
            }
            else
            {
                resetData();//IDLE_STATUS;
            }
            
            break;
        }
        default:
            resetData();
            break;
    }
}

void resetData(void)
{
    step = IDLE_STATUS;
    idx = INIT_VALUE;
    ctr = INIT_VALUE;
    addr = INIT_VALUE;
    data_ptr = NULL;
    unpack_ptr = NULL;
    counts = INIT_VALUE;
    NumFirst = INIT_VALUE;
    NumSecond = INIT_VALUE;
    crc16 = INIT_VALUE;
    num = INIT_VALUE;
    len = INIT_VALUE;
    memset(buf, 0xFF, MAX_SIZE);
}


