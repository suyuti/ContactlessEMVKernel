#include <stdlib.h>
#include "./kernel.h"
#include "./err.h"

card_open       gCardOpen       = NULL;
card_close      gCardClose      = NULL;
card_reset      gCardReset      = NULL;
card_transmit   gCardTransmit   = NULL;

//------------------------------------------------------------------------------------

int initialize()
{
    // 1. Set terminal parameters
    gCardOpen();
    gCardReset();
    unsigned char cmd[] = {0x00, 0xA4, 0x04, 0x00,
                                    0x0D,
                                    '2', 'P', 'A', 'Y', '.', 'S', 'Y', 'S', '.', 'D', 'D', 'F', '0', '1', };
    unsigned char resp[10] = {0x00};
    unsigned long len = 0;
    gCardTransmit(cmd, sizeof(cmd), resp, &len);

    unsigned char cmd2[] = {0x00, 0xA4, 0x04, 0x00};
    gCardTransmit(cmd2, sizeof(cmd2), resp, &len);
    //gCardTransmit(cmd2, sizeof(cmd2), resp, &len);
    // 2. Set HAL interfaces
    return 0;
}

//------------------------------------------------------------------------------------

int release()
{
    return 0;
}

//------------------------------------------------------------------------------------

int start()
{
    return 0;
}

//------------------------------------------------------------------------------------

int getVersion()
{
    return 99;
}

//------------------------------------------------------------------------------------

int setCardOpen(card_open f)
{
    gCardOpen = f;
    return SUCCESS;
}

//------------------------------------------------------------------------------------

int setCardReset(card_reset f)
{
    gCardReset = f;
    return SUCCESS;
}

//------------------------------------------------------------------------------------

int setCardClose(card_close f)
{
    gCardClose = f;
    return SUCCESS;
}

//------------------------------------------------------------------------------------

int setCardTransmit(card_transmit f)
{
    gCardTransmit = f;
    return SUCCESS;
}
