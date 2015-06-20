#include <string.h> // memset
#include "epConfig.h"
#include "../Base/err.h"

int resetEpConfig(EpConfigPtr p)
{
    if (!p) return INVALID_PARAMETER;
    memset(p, 0x00, sizeof(EpConfig));
    return SUCCESS;
}

//-----------------------------------------------------------------

int parseEpconfig(EpConfigPtr obj, const char* line) 
{
    int i = 0;
    char *token = strtok(line, ".");
    while(token) {
        switch(i++) {
            case 0: // Status check 
            {
                RESET_STATUS_CHECK(*obj);
                if (token != NULL) {
                    if (token[0] == '1')
                        SET_STATUS_CHECK(*obj);
                }
            }
            break;
            case 1: // Zero amount allowed 
            {
                RESET_ZERO_AMOUT_ALLOWED(*obj);
                if (token != NULL) {
                    if (token[0] == '1')
                        SET_ZERO_AMOUT_ALLOWED(*obj);
                }
            }
            break;
            case 2: // clessTrnxLimit 
            {
                if (token != NULL) {
                    SET_EXIST_CLESS_TRNX_LIMIT(*obj);
                    obj->clessTrnxLimit = atoi(token);
                }
            }
            break;
            case 3: // clessFloorLimit
            {
                if (token != NULL) {
                    SET_EXIST_CLESS_FLOOR_LIMIT(*obj);
                    obj->clessFloorLimit = atoi(token);
                }
            }
            break;
            case 4: // termFloorLimit
            {
                if (token != NULL) {
                    SET_EXIST_TERM_FLOOR_LIMIT(*obj);
                    obj->termFloorLimit = atoi(token);
                }
            }
            break;
            case 5: // cvmRequiredLimit
            {
                if (token != NULL) {
                    SET_EXIST_CVM_REQ_LIMIT(*obj);
                    obj->cvmRequiredLimit = atoi(token);
                }
            }
            break;
            case 6: // ttq
                if (token != NULL) {
                    SET_EXIST_TTQ(*obj);
                    memcpy(obj->ttq, token, strlen(token));
                }
            break;
            case 7: // extendedSelectionSupport
            {
                RESET_EXIST_EXTENDED_SELECTION_SUPP(*obj);
                if (token != NULL) {
                    if (token[0] == '1')
                        SET_EXIST_EXTENDED_SELECTION_SUPP(*obj);
                }
            }
            break;
        }
        token = strtok(NULL, ".");
    }    
    return SUCCESS;
}

//-----------------------------------------------------------------

int readEpConfig(const char configName, EpConfigPtr pConfig)
{
    
    return SUCCESS;
}

//-----------------------------------------------------------------

int addEpConfig(EpConfigsPtr pConfigs, EpConfig config)
{
    if (!pConfigs) return NULL_PARAMETER;
    if (pConfigs->count >= MAX_EP_CONFIG) return INDEX_OUT_OF_RANGE;

    memcpy(pConfigs + pConfigs->count, &config, sizeof(EpConfig));
    pConfigs->count++;

    return SUCCESS;
}

//-----------------------------------------------------------------

int resetEpConfigs(EpConfigsPtr pConfigs)
{
    if (!pConfigs) return NULL_PARAMETER;
    memset(pConfigs, 0x00, sizeof(EpConfigs));
    return SUCCESS;
}
