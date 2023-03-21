

#include "../Header/pack.h"
#include "../Header/protocol.h"
#include "../Header/unpack.h"

extern AnalysisFunc driverBoardAnalysisParse;
extern AnalysisFunc usBoardAnalysisParse;
extern AnalysisFunc valveBoardAnalysisParse;
extern AnalysisFunc motorBoardAnalysisPrase;

    void Unpack (uint8_t *buf,uint8_t len)
{
    unsigned int idx = 0;
    while(idx < len){
        uint8_t ctr;
        ctr = buf[idx];
        switch(ctr){
            case DRIVERBOARD:
            {
                ++ idx;
                idx += (*driverBoardAnalysisParse)(&buf[idx]);
                break;
            }
            case ULTRASONIC:
            {
                ++ idx;
                idx += (*usBoardAnalysisParse)(&buf[idx]);
                break;
            }
            case VALVE:
            {
                ++ idx;
                idx += (*valveBoardAnalysisParse)(&buf[idx]);
                break;
            }
            case MOTOR:
            {
                ++ idx;
                idx += (*motorBoardAnalysisPrase)(&buf[idx]);
                break;
            }
            default:
            {
                break;
            }
        }
    }
}