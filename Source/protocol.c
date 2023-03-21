#include "../Header/protocol.h"


AnalysisFunc driverBoardAnalysisParse;
AnalysisFunc usBoardAnalysisParse;
AnalysisFunc valveBoardAnalysisParse;
AnalysisFunc motorBoardAnalysisPrase;

SendFunc driverBoardSendParse;
SendFunc usBoardSendParse;
SendFunc valveBoardSendParse;
SendFunc motorBoardSendPrase;

/*CRC16校验*/
uint16_t CRC16_Check (const uint8_t *data,uint8_t len)
{
    uint16_t CRC16 = 0xFFFF;
    uint8_t state,i,j;
    for(i = 0; i < len; i++ )
    {
        CRC16 ^= data[i];
        for( j = 0; j < 8; j++)
        {
            state = CRC16 & 0x01;
            CRC16 >>= 1;
            if(state)
            {
                CRC16 ^= 0xA001;
            }
        }
    }
    return CRC16;
}

void initAnalysisInterface(unsigned char type, AnalysisFunc pFunc)
{
    switch (type)
    {
    case DRIVERBOARD:
    {
        driverBoardAnalysisParse = pFunc;
        break;
    }
    case ULTRASONIC:
    {
        usBoardAnalysisParse = pFunc;
        break;
    }
    case VALVE:
    {
        valveBoardAnalysisParse = pFunc;
        break;
    }
    case MOTOR:
    {
        motorBoardAnalysisPrase = pFunc;
        break;
    }
    default:
        break;
    }
}

void initSendInterface(unsigned char type, SendFunc pFunc)
{
    switch (type)
    {
        case DRIVERBOARD:
        {
            driverBoardSendParse = pFunc;
            break;
        }
        case ULTRASONIC:
        {
            usBoardSendParse= pFunc;
            break;
        }
        case VALVE:
        {
            valveBoardSendParse = pFunc;
            break;
        }
        case MOTOR:
        {
            motorBoardSendPrase= pFunc;
            break;
        }
        default:
            break;
    }
}