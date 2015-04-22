#include <stdlib.h>
#include "unPredNumGen.h"
#include "../../Base/err.h"

int generateUnpredictableNumberDefaultImpl(unsigned char* p, long* pSize)
{
    if (!p || !pSize) return INVALID_PARAMETER;
    int i = 0;
    for (i = 0; i < *pSize; ++i) {
        p[i] = rand() % 0xFF;
    }
    return SUCCESS;
}
