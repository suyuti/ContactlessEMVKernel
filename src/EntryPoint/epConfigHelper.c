#include <stdlib.h>
#include "./epConfigHelper.h"
#include "./epCommon.h"
#include "../Base/err.h"

int readConfig(const char* configName, EpConfigPtr configPtr)
{
    int file = FILE_OPEN_R(&gEp.hal, configName);
    if (file == NULL) { 
        printf("Dosya yok!");
        return FILE_NOT_FOUND; 
    }
    int size = GET_FILE_SIZE(&gEp.hal, file);

    char *tmp = (char*)ALLOCATE(&gEp.hal, size+1);
    if (!tmp) { goto EXIT;}
    memset(tmp, 0x00, size);
    FILE_READ(&gEp.hal, file, tmp, size);



EXIT:
    RELEASE(&gEp.hal, tmp);
    FILE_CLOSE(&gEp.hal, file);

    return SUCCESS;
}

