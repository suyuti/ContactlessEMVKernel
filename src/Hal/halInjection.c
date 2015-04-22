#include "halInjection.h"

int injectInterface(HalInterfacesPtr p, HalInterfaceTypes t, void* fp)
{
    switch(t) {
        case RandomNumberGenerator:
            p->_genUnPredNum = (genUnPredNum)fp;
        break;
        case CardReaderOpen:
        break;
        case CardReaderClose:
        break;
    }
    return 0;
}