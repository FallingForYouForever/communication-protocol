#include "../Header/send.h"
#include "../Header/protocol.h"

extern SendFunc driverBoardSendParse;
extern SendFunc usBoardSendParse;
extern SendFunc valveBoardSendParse;
extern SendFunc motorBoardSendPrase;

void send (unsigned char mode, char *buf, unsigned int len)
{
        switch(mode){
            case DRIVERBOARD:
            {
                (*driverBoardSendParse)(buf,len);
                break;
            }
            case ULTRASONIC:
            {
                (*usBoardSendParse)(buf,len);
                break;
            }
            case VALVE:
            {
                (*valveBoardSendParse)(buf,len);
                break;
            }
            case MOTOR:
            {
               (*motorBoardSendPrase)(buf,len);
               break;
            }
            default:
            {
                break;
            }
        }



}
