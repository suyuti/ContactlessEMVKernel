#include <string.h> // memset

#include "./fci.h"
#include "./err.h"

//-----------------------------------------------------------------------

int _clearFci(FciPtr r)
{
    if (!r) return NULL_PARAMETER;
    memset(r, 0x00, sizeof(Fci));
    return SUCCESS;
}

//-----------------------------------------------------------------------

int _setFciIssData(FciPtr r, int tag, const unsigned char* value, int size)
{
    if (!r || !value || size == 0) return NULL_PARAMETER;
    if (r->_fciIssDataCount == 0) return INDEX_OUT_OF_RANGE;
    /*
    printf("------set Fci %02X l:%02X(%d) v: ", tag, size, size);
    int i = 0;
    for (i = 0; i < size; ++i) {
        printf("%02X ", value[i]);
    }
    printf("\n");
    */

    switch(tag) {
        case 0x4F:
            if (size > 16) return INCORRECT_DATA;
            r->_fciIssData[r->_fciIssDataCount-1]._4F[0] = size;
            memcpy(r->_fciIssData[r->_fciIssDataCount-1]._4F+1, value, size);
        break;
        case 0x50:
            if (size > 16) return INCORRECT_DATA;
            r->_fciIssData[r->_fciIssDataCount-1]._50[0] = size;
            memcpy(r->_fciIssData[r->_fciIssDataCount-1]._50+1, value, size);
        break;
        case 0x87:
            if (size > 1) return INCORRECT_DATA;
            r->_fciIssData[r->_fciIssDataCount-1]._87[0] = size;
            memcpy(r->_fciIssData[r->_fciIssDataCount-1]._87+1, value, size);
        break;
        case 0x9F2A:
            if (size > 1) return INCORRECT_DATA;
            r->_fciIssData[r->_fciIssDataCount-1]._9F2A[0] = size;
            memcpy(r->_fciIssData[r->_fciIssDataCount-1]._9F2A+1, value, size);
        break;
        default:
            return UNKNOWN_TAG; 
        break;
    }
    return SUCCESS;
}

//-----------------------------------------------------------------------

int _set84(FciPtr r, const unsigned char* val, int size)
{
    r->_84[0] = 0x01;
    memcpy(r->_84+1, val, size);
    return SUCCESS;
}

//-----------------------------------------------------------------------

int _incFciIssDataCounter(FciPtr r)
{
    if (!r) return NULL_PARAMETER;
    if (r->_fciIssDataCount>=10) return INDEX_OUT_OF_RANGE;
    r->_fciIssDataCount++;
    return SUCCESS;
}

int getAdfNameLen(FciPtr p, int index)
{
    //if (!p) return NULL_PARAMETER;
    //if (index < 0 || index >= p->_fciIssDataCount) return INDEX_OUT_OF_RANGE;
    return (int)p->_fciIssData[index]._4F[0];
}

unsigned char* getAdfName(FciPtr p, int index)
{
    //if (!p) return NULL;
    //if (index < 0 || index >= p->_fciIssDataCount) return NULL;
    return &(p->_fciIssData[index]._4F[1]);
}

int getApplicationLabelLen(FciPtr p, int index)
{
    //if (!p) return NULL_PARAMETER;
    //if (index < 0 || index >= p->_fciIssDataCount) return INDEX_OUT_OF_RANGE;
    return &(p->_fciIssData[index]._50[0]);
}

unsigned char* getApplicationLabel(FciPtr p, int index)
{
    //if (!p) return NULL;
    //if (index < 0 || index >= p->_fciIssDataCount) return NULL;
    return &(p->_fciIssData[index]._50[1]);
}

int getAPILen(FciPtr p, int index)
{
    //if (!p) return NULL_PARAMETER;
    //if (index < 0 || index >= p->_fciIssDataCount) return INDEX_OUT_OF_RANGE;
    return (int)p->_fciIssData[index]._87[0];
}

int getAPI(FciPtr p, int index)
{
    //if (!p) return NULL_PARAMETER;
    //if (index < 0 || index >= p->_fciIssDataCount) return INDEX_OUT_OF_RANGE;
    return (int)p->_fciIssData[index]._87[1];
}


int getKernelIdLen(FciPtr p, int index)
{
    //if (!p) return NULL_PARAMETER;
    //if (index < 0 || index >= p->_fciIssDataCount) return INDEX_OUT_OF_RANGE;
    return (int)p->_fciIssData[index]._9F2A[0];
}

int getKernelId(FciPtr p, int index)
{
    //if (!p) return NULL_PARAMETER;
    //if (index < 0 || index >= p->_fciIssDataCount) return INDEX_OUT_OF_RANGE;
    return (int)p->_fciIssData[index]._9F2A[1];
}

