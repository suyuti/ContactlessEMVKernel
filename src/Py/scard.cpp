#include <stdio.h>
#include <stdlib.h>
#include <winscard.h>
#include <wintypes.h>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>

using namespace std;
static SCARDCONTEXT         hContext;
static string               _selectedReader;
static SCARD_IO_REQUEST     actIoProtocol;
static SCARDHANDLE          hCard;


int GetReaderList(vector<string>& readerList)
{
    SCARDCONTEXT    hContext;
    DWORD           dwReaders = SCARD_AUTOALLOCATE;
    LPTSTR          pmszReaders = NULL;
    LPTSTR          pReader;
    LONG            rv;


    rv = SCardEstablishContext(SCARD_SCOPE_SYSTEM, NULL, NULL, &hContext);
    if (rv != SCARD_S_SUCCESS) {
        return -1;//SCARD_INIT_FAILED;
    }

    rv = SCardListReaders(hContext, NULL, (LPTSTR)&pmszReaders, &dwReaders);
    if (rv != SCARD_S_SUCCESS) {
        return -2;//SCARD_READERLIST_ERROR;
    }

    pReader = pmszReaders;
    while (*pReader != '\0') {
        readerList.push_back(pReader);
        pReader = pReader + strlen(pReader) + 1;
    }

    rv = SCardFreeMemory(hContext, pmszReaders);
    SCardReleaseContext(hContext);

    return 0;
}

//-----------------------------------------------------------------------------------------------------------

string SelectReader(int defaultReader = -1)
{
    vector<string> readerList;
    unsigned short rv;

    cout << "defaultReader: " << defaultReader << endl;

    rv = GetReaderList(readerList);
    if (rv != 0) {
        cout << "Reader list error. " << rv << endl;
        //throw new std::exception();
        return "91";
        //return;
    }

    if (defaultReader == -1) {
        cout << "Select reader:" << endl;
    }
    vector<string>::iterator it = readerList.begin();
    int index = 0;
    if (defaultReader==-1) {
        for(;it != readerList.end(); ++it) {
            cout << ++index << ". " << *it << endl;
        }
    }
    int selection;
    if (defaultReader==-1) {
        do {
            cin >> selection;
        } while(selection > index);
    }
    else {
        selection = defaultReader;
    }

    _selectedReader = readerList[selection - 1];
    //cout << _selectedReader << " will be used." << endl;
    return _selectedReader;
}

//-----------------------------------------------------------------------------------------------------------

int ResetCard()
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
                       _selectedReader.c_str(),
                       shareMode,
                       preferedProtocol,
                       &hCard,
                       &activeProtocol);
    if (rv != SCARD_S_SUCCESS) {
        cout<<"Cardconnect error:"<<rv<<endl;
        return -2;//SCARD_CONNECT_FAILED;
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

//-----------------------------------------------------------------------------------------------------------

int Disconnect()
{
    if (SCardDisconnect(hCard, SCARD_EJECT_CARD) == SCARD_S_SUCCESS) {
        SCardReleaseContext(hContext);
        return 0;//OK;
    }
    return -1;//SCARD_REJECT_FAILED;
}

//-----------------------------------------------------------------------------------------------------------

int Transmit(const unsigned char*  pInBuffer,
                 unsigned long         inSize,
                 unsigned char*        pOutBuffer,
                 unsigned long*        pOutSize)
{
    *pOutSize = 255; // TODO
    long rv = SCardTransmit(hCard,
                //(LPSCARD_IO_REQUEST)g_actIoProtocol.dwProtocol,
                &actIoProtocol,
                pInBuffer,
                inSize,
                NULL,
                pOutBuffer,
                pOutSize);
    cout << "> ";
    for(int i = 0; i < inSize; ++i) {
        printf("%02X ", pInBuffer[i]);
    }
    cout << endl;
    cout << "< ";
    for(int i = 0; i < *pOutSize; ++i) {
        printf("%02X ", pOutBuffer[i]);
    }
    cout << endl;

    if (rv != SCARD_S_SUCCESS) {
        return -1;//SMARTCARD_FAIL;//SCARD_TRANSMIT_FAILED;
    }

    return 0;//SMARTCARD_OK;//OK;
}

//-----------------------------------------------------------------------------------------------------------
// 0123
int str2bcd(string str, unsigned char* pOut) 

{
    if ((str.size() % 2) != 0) return 0;
    int j = 0;
    char c;
    for(int i = 0; i<str.size();++i) {
        c = str[i];
        if (c>='0' && c<='9') {
            c -= '0';
        }
        else if (c>='a' && c<='f') {
            c -= 'a';
            c+=0x0A;
        }
        else if (c>='A' && c<='F') {
            c -= 'A';
            c+=0x0A;
        }
        else {
            return 0;
        }

        if ((i%2) == 0) {
            pOut[j] = c << 4;
        }
        else {
            pOut[j] |= c & 0x0f;
            j++;
        }
    }
    return j;
}

string bcd2str(unsigned char* pIn, int size) 

{
    if (size <= 0 || pIn == NULL) return "";
    char c, t;
    string s = "";
    for (int i = 0;i < size; ++i) {
        c = pIn[i] >> 4;
        if (c >= 0x00 && c <= 0x09) {
            c += '0';
        }
        else if (c>=0x0A && c <= 0x0F) {
            c += 'A' - 0x0a;
        }
        s += c;

        c = pIn[i] & 0x0F;
        if (c >= 0x00 && c <= 0x09) {
            c += '0';
        }
        else if (c>=0x0A && c <= 0x0F) {
            c += 'A' - 0x0A;
        }
        s += c;
    }
    return s;
}

string Transmit2(string apdu) 
{
    unsigned char inBuffer[1024] = {0x00};
    unsigned long inBufferSize = 0;
    unsigned char outBuffer[1024] = {0x00};
    unsigned long outBufferSize = 255;

    inBufferSize = str2bcd(apdu, inBuffer);

    long rv = SCardTransmit(hCard,
                            &actIoProtocol,
                            inBuffer,
                            inBufferSize,
                            NULL,
                            outBuffer,
                            &outBufferSize);
    if (rv != SCARD_S_SUCCESS) {
        return "";
    }
    return bcd2str(outBuffer, outBufferSize);
}

//-----------------------------------------------------------------------------------------------------------



