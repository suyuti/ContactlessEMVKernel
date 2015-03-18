#include <winscard.h>
#include <wintypes.h>
#include <stddef.h>
#include <stdio.h>
#include "scard.h"

static SCARDCONTEXT         hContext;
static SCARD_IO_REQUEST     actIoProtocol;
static SCARDHANDLE          hCard;
static char                 gSelectedReaderName[128] = "SCM SDI 010 [Vendor Interface] (21120706200335) 00 00";

int reset()
{
    DWORD activeProtocol    = 0;
    DWORD shareMode         = SCARD_SHARE_SHARED;
    DWORD preferedProtocol  = SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1;
    LONG  rv;

    rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);
    if (rv != SCARD_S_SUCCESS) {
        return -1;//SCARD_INIT_FAILED;
    }

    rv = SCardConnect(hContext,
                        gSelectedReaderName,
                       shareMode,
                       preferedProtocol,
                       &hCard,
                       &activeProtocol);
    if (rv != SCARD_S_SUCCESS) {
        return -2;
    }

    actIoProtocol.cbPciLength = sizeof(SCARD_IO_REQUEST);

    if (activeProtocol == SCARD_PROTOCOL_T0) {
        actIoProtocol = *SCARD_PCI_T0;
        //g_actIoProtocol.dwProtocol = (unsigned long) SCARD_PCI_T0;
    }
    else if (activeProtocol == SCARD_PROTOCOL_T1) {
        actIoProtocol = *SCARD_PCI_T1;
        //g_actIoProtocol.dwProtocol = (unsigned long) SCARD_PCI_T1;
    }
    else {
        return -3;//SCARD_CONNECT_FAILED;
    }

    return 0;//SMARTCARD_OK;//OK;
}

int sendrecv(const unsigned char* pIn, int inSize, unsigned char* pOut, unsigned long* pOutSize)
{
    printf("[TERM: %3d]> ", inSize);
    int i = 0;
    for(i = 0; i < inSize; ++i) {
        if ((i%10)==0 && i!=0) {
            printf("\n             ");
        }
        printf("%02X ", pIn[i]);
    }
    printf("\n");

    *pOutSize = 255;
    long rv = SCardTransmit(hCard,
                            &actIoProtocol,
                            pIn,
                            inSize,
                            NULL,
                            pOut,
                            pOutSize);
    if (rv != SCARD_S_SUCCESS) {
        *pOutSize = 0;
        return rv;
    }

    printf("[CARD: %3d]< ", (int)*pOutSize);
    for(i = 0; i < *pOutSize; ++i) {
        if ((i%10)==0 && i!=0) {
            printf("\n             ");
        }
        printf("%02X ", pOut[i]);
    }
    printf("\n");
    return 0;
}

int close()
{
    if (SCardDisconnect(hCard, SCARD_EJECT_CARD) == SCARD_S_SUCCESS) {
        SCardReleaseContext(hContext);
        return 0;//OK;
    }
    return -1;//SCARD_REJECT_FAILED;
}