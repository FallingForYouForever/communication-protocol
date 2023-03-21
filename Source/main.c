
#include "stdio.h"
#include "../Header/pack.h"
#include "../Header/protocol.h"
#include "../Header/unpack.h"
#include "../Header/receive.h"

int main ()
{
    /*******Test*******/
    uint8_t i,j,num=1,checklen=0,ctr=0,addr=0,framelen=0;
    uint8_t fra[MAX_SIZE];
    uint16_t len=0;

    PACK_BEGIN(fra, len);
    /*******Pack1*******/
    ctr=0x00;addr=0x11;
    uint8_t data[2] = { 0x22,0x33 };
    PACKITEM(ctr, addr, data, sizeof(data));
    /*******Pack2*******/
    ctr=0x00;addr=0x44;
    uint8_t datas[2] = { 0x55,0x66 };
    PACKITEM(ctr, addr, datas, sizeof(datas));
    PACK_END();
    printf("%d\n",len);
    //std::cout<<std::hex<<+getLen(fra)<<" ";

    printf("*****Packed Frame*****\n");
    for(i=0;i<17;i++){
        printf("%x",fra[i]);
        printf(" ");
    }
    printf("\n");

    //std::cout<<std::endl;
    printf("*****UnPacked Frame*****\n");
    /*******UnPack*******/
    for(i=0;i<17;i++){
        Receive(fra[i]);
    }





}
