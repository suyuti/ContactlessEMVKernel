/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#include <string.h>  // memset
#include <stddef.h>
#include <stdlib.h>  // atoi
#include "epConfig.h"
#include "../Common/err.h"
#include "epCommon.h"
#include "../Common/hal.h"

//-----------------------------------------------------------------------------

int clearEpConfigData(EpConfigDataPtr obj)
{
    if (!obj) return NULL_PARAMETER;
    memset(obj, 0x00, sizeof(EpConfigData));
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int clearEpConfigs(EpPtr pEp)
{
    if (!pEp) return NULL_PARAMETER;

    memset(pEp->epConfigs, 0x00, sizeof(EpConfig)*MAX_EP_CONFIG);
    pEp->epConfigsCount = 0;
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int addEpConfig(EpPtr pEp, EpConfig config)
{
    if (!pEp) return NULL_PARAMETER;
    if (pEp->epConfigsCount >= MAX_EP_CONFIG) {
        return INDEX_OUT_OF_RANGE;
    }
    pEp->epConfigs[pEp->epConfigsCount] = config;
    pEp->epConfigsCount++;
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int findEpConfig(EpPtr pEp, const char* aid, unsigned char kid, EpConfigPtr obj)
{
    if (!pEp || !obj) return NULL_PARAMETER;
    int i = 0;
    for (i = 0; i < pEp->epConfigsCount; ++i) {
        if (strcmp(pEp->epConfigs[i].aid, aid) == 0 &&
            pEp->epConfigs[i].kid == kid) {
            *obj = pEp->epConfigs[i];
            return SUCCESS;
        }
    }
    return OBJECT_NOT_FOUND;
}

//-----------------------------------------------------------------------------

int loadConfigs(EpPtr pEp)
{
    int count = 0;
    if (!pEp) return NULL_PARAMETER;

    int file = fileOpen(pEp->configFolder, "r");
    if (file == -1) {
        return FILE_NOT_FOUND;
    }
    int size = getFileSize(file);

    char *tmp = (char*)allocate(size+1);
    if (!tmp) { goto EXIT;}
    memset(tmp, 0x00, size);
    fileRead(file, tmp, size);

    clearEpConfigs(pEp);
    int i = 0;
    int j = 0;
    EpConfig config;
    char aid[30] = {0x00};
    unsigned char kid;
    char line[120] = {0x00};

    int part = 0;
    while(i < size) {
        if (tmp[i] == ':') {
            line[j] = '\0';
            j++;
            switch(part) {
                case 0:
                    strcpy(aid, line);
                    part++;
                break;
                case 1:
                    if (line[0] >= '0' && line[0] <= '9') {
                        kid = line[0] - '0';
                    } else if (line[0] >= 'A' && line[0] <= 'F') {
                        kid = line[0] - 'A' + 0x0A;
                    }
                    kid <<= 4;

                    if (line[1] >= '0' && line[1] <= '9') {
                        kid |= line[1] - '0';
                    } else if (line[1] >= 'A' && line[1] <= 'F') {
                        kid |= line[1] - 'A' + 0x0A;
                    }
                    part++;
                break;
                case 2:
                    //! parseEpconfig(&config, line);
                    part = 0;
                break;
            }
            j = 0;
        } else if (tmp[i] == '\n') {
            if (part == 2) {
                memset(&config, 0x00, sizeof(EpConfig));
                parseEpconfig(&(config.configData), line);
                strcpy(config.aid, aid);
                config.kid = kid;
                addEpConfig(pEp, config);
                count++;
            }
            part = 0;
            j = 0;
        } else {
            line[j] = tmp[i];
            j++;
        }
        i++;
    }

EXIT:
    release(tmp);
    fileClose(file);

    return count;
}

//-----------------------------------------------------------------------------

int parseEpconfig(EpConfigDataPtr obj, const char* line)
{
    const char delimiters[] = ".";
    char *running;
    char *token;
    int  i= 0;

    memset(obj, 0x00, sizeof(EpConfigData));

    while((token = strsep (&line, delimiters))) {
        switch(i++) {
            case 0:  // Status check
            {
                RESET_STATUS_CHECK(*obj);
                if (token[0] != 0x00) {
                    if (token[0] == '1')
                    SET_STATUS_CHECK(*obj);
                }
            }
                break;
            case 1:  // Zero amount allowed
            {
                RESET_ZERO_AMOUT_ALLOWED(*obj);
                if (token[0] != 0x00) {
                    if (token[0] == '1')
                        SET_ZERO_AMOUT_ALLOWED(*obj);
                }
            }
                break;
            case 2:  // clessTrnxLimit
            {
                if (token[0] != 0x00) {
                    SET_EXIST_CLESS_TRNX_LIMIT(*obj);
                    obj->clessTrnxLimit = atoi(token);
                }
            }
                break;
            case 3:  // clessFloorLimit
            {
                if (token[0] != 0x00) {
                    SET_EXIST_CLESS_FLOOR_LIMIT(*obj);
                    obj->clessFloorLimit = atoi(token);
                }
            }
                break;
            case 4:  // termFloorLimit
            {
                if (token[0] != 0x00) {
                    SET_EXIST_TERM_FLOOR_LIMIT(*obj);
                    obj->termFloorLimit = atoi(token);
                }
            }
                break;
            case 5:  // cvmRequiredLimit
            {
                if (token[0] != 0x00) {
                    SET_EXIST_CVM_REQ_LIMIT(*obj);
                    obj->cvmRequiredLimit = atoi(token);
                }
            }
                break;
            case 6:  // ttq
                if (token[0] != 0x00) {
                    SET_EXIST_TTQ(*obj);
                    int _i = 0;
                    str2bcd(token, strlen(token), obj->ttq, &_i);
                }
                break;
            case 7:  // extendedSelectionSupport
            {
                RESET_EXTENDED_SELECTION_SUPP(*obj);
                if (token[0] != 0x00) {
                    if (token[0] == '1')
                        SET_EXTENDED_SELECTION_SUPP(*obj);
                }
            }
                break;
        }
    }
    return SUCCESS;
}


int getEpConfigAidLen(EpConfigPtr p)
{
    // if (!p) return NULL_PARAMETER;
    return (int)(p->aid[0]);
}

unsigned char* getEpConfigAid(EpConfigPtr p)
{
    return (unsigned char*)p->aid;
}



/*



































#define MAX_AID_KID     200
#define MAX_EP_CONFIG   (12*17)

static Aid_Kid      gsAidKidList[MAX_AID_KID];
static EpConfigData     gsEpConfigs[MAX_EP_CONFIG];
static int          gsAidKidIndex   = 0;
static int          gsEpConfigIndex = 0;

//-----------------------------------------------------------------

int getConfigCount(EpConfigDataPtr pConfigList)
{
    return gsEpConfigIndex;
}

//-----------------------------------------------------------------

EpConfigDataPtr findConfigByAidKid(const char* aid, char kid)
{
    int i = 0;
    for (i = 0; i < gsAidKidIndex; ++i) {
        if ((strcmp(gsAidKidList[i].aid, aid) == 0) &&
             gsAidKidList[i].kid == kid) {
            return &(gsEpConfigs[i]);
        }
    }
    return NULL;
}

//-----------------------------------------------------------------

int addConfigByAidKid(const char* aid, unsigned char kid, EpConfigData epConfig)
{
    if (gsAidKidIndex >= MAX_AID_KID ||
        gsEpConfigIndex >= MAX_EP_CONFIG)
        return INDEX_OUT_OF_RANGE;

    Aid_KidPtr pAidKid = &(gsAidKidList[gsAidKidIndex]);

    strcpy(pAidKid->aid, aid);
    pAidKid->kid = kid;

    gsEpConfigs[gsEpConfigIndex] = epConfig;
    pAidKid->configIndex = gsEpConfigIndex;

    gsEpConfigIndex++;
    gsAidKidIndex++;

    return SUCCESS;
}

//-----------------------------------------------------------------

int resetAllConfigs()
{
    memset(&gsAidKidList,     0x00, sizeof(gsAidKidList));
    memset(&gsEpConfigs,   0x00, sizeof(gsEpConfigs));
    gsEpConfigIndex = 0;
    gsAidKidIndex   = 0;
    return SUCCESS;
}

//-----------------------------------------------------------------




//-----------------------------------------------------------------
// TODO
//- Testing purposes
int t_getAidKidCount() {return gsAidKidIndex;}
int t_getEpConfigCount() {return gsEpConfigIndex;}
Aid_KidPtr t_getAidKid() { return gsAidKidList;}
EpConfigPtr t_getEpConfig() {return gsEpConfigs;}




//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------
//-----------------------------------------------------------------

int resetEpConfig(EpConfigPtr p)
{
    if (!p) return INVALID_PARAMETER;
    memset(p, 0x00, sizeof(EpConfig));
    return SUCCESS;
}

//-----------------------------------------------------------------


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
*/


void t_printEpConfig(const EpConfigDataPtr p)
{
    printf("Status check [%s] ", IS_EXIST_STATUS_CHECK(*p) ? "YES" : "NO");
    if (IS_EXIST_STATUS_CHECK(*p))
        printf(": %02X", p->statusCheck);
    printf("\n");

    printf("Zero amount allowed [%s] ", IS_EXIST_ZERO_AMOUNT_ALLOWED(*p) ? "YES" : "NO");
    if (IS_EXIST_ZERO_AMOUNT_ALLOWED(*p))
        printf(": %02X", p->zeroAmountAllowed);
    printf("\n");

    printf("Cless Trnx Limit [%s] ", IS_EXIST_CLESS_TRNX_LIMIT(*p) ? "YES" : "NO");
    if (IS_EXIST_CLESS_TRNX_LIMIT(*p))
        printf(": %d", p->clessTrnxLimit);
    printf("\n");

    printf("Cless Floor Limit [%s] ", IS_EXIST_CLESS_FLOOR_LIMIT(*p) ? "YES" : "NO");
    if (IS_EXIST_CLESS_FLOOR_LIMIT(*p))
        printf(": %d", p->clessFloorLimit);
    printf("\n");

    printf("Term Floor Limit [%s] ", IS_EXIST_TERM_FLOOR_LIMIT(*p) ? "YES" : "NO");
    if (IS_EXIST_TERM_FLOOR_LIMIT(*p))
        printf(": %d", p->termFloorLimit);
    printf("\n");

    printf("Cvm Req Limit [%s] ", IS_EXIST_CVM_REQ_LIMIT(*p) ? "YES" : "NO");
    if (IS_EXIST_CVM_REQ_LIMIT(*p))
        printf(": %d", p->cvmRequiredLimit);
    printf("\n");

    printf("TTQ [%s] ", IS_EXIST_TTQ(*p) ? "YES" : "NO");
    if (IS_EXIST_TTQ(*p)) {
        printf(": %02X", p->ttq[0]);
        printf(" %02X", p->ttq[1]);
        printf(" %02X", p->ttq[2]);
        printf(" %02X", p->ttq[3]);
    }
    printf("\n");

    printf("Ext Sel Sup[%s] ", IS_EXIST_EXTENDED_SELECTION_SUPP(*p) ? "YES" : "NO");
    if (IS_EXIST_EXTENDED_SELECTION_SUPP(*p))
        printf(": %02X", p->extendedSelectionSupport);
    printf("\n");
}

