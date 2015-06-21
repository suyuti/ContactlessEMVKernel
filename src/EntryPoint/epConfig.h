#ifndef _EP_CONFIG_H_
#define _EP_CONFIG_H_

#include "../Base/general.h"

//--------------------------------------------------------------------
// Book A, Table 5-2

typedef struct {
    unsigned char   bitmap;
    unsigned char   statusCheck;
    unsigned char   zeroAmountAllowed;
    int             clessTrnxLimit;
    int             clessFloorLimit;
    int             termFloorLimit;
    int             cvmRequiredLimit;
    unsigned char   ttq[4];
    unsigned char   extendedSelectionSupport;
} EpConfig, *EpConfigPtr;

int resetEpConfig(EpConfigPtr p);
int readEpConfig(const char configName, EpConfigPtr pConfig);

#define IS_EXIST_STATUS_CHECK(p)                ((p).bitmap && 0x01)        
#define IS_EXIST_ZERO_AMOUNT_ALLOWED(p)         ((p).bitmap && 0x02)
#define IS_EXIST_CLESS_TRNX_LIMIT(p)            ((p).bitmap && 0x04)
#define IS_EXIST_CLESS_FLOOR_LIMIT(p)           ((p).bitmap && 0x08)
#define IS_EXIST_TERM_FLOOR_LIMIT(p)            ((p).bitmap && 0x10)
#define IS_EXIST_CVM_REQ_LIMIT(p)               ((p).bitmap && 0x20)
#define IS_EXIST_TTQ(p)                         ((p).bitmap && 0x40)
#define IS_EXIST_EXTENDED_SELECTION_SUPP(p)     ((p).bitmap && 0x80)

#define SET_EXIST_STATUS_CHECK(p)               ((p).bitmap |= 0x01)        
#define SET_EXIST_ZERO_AMOUNT_ALLOWED(p)        ((p).bitmap |= 0x02)
#define SET_EXIST_CLESS_TRNX_LIMIT(p)           ((p).bitmap |= 0x04)
#define SET_EXIST_CLESS_FLOOR_LIMIT(p)          ((p).bitmap |= 0x08)
#define SET_EXIST_TERM_FLOOR_LIMIT(p)           ((p).bitmap |= 0x10)
#define SET_EXIST_CVM_REQ_LIMIT(p)              ((p).bitmap |= 0x20)
#define SET_EXIST_TTQ(p)                        ((p).bitmap |= 0x40)
#define SET_EXIST_EXTENDED_SELECTION_SUPP(p)    ((p).bitmap |= 0x80)


#define SET_STATUS_CHECK(p)                     (p).statusCheck                 = SET; SET_EXIST_STATUS_CHECK(p)
#define SET_ZERO_AMOUT_ALLOWED(p)               (p).zeroAmountAllowed           = SET; SET_EXIST_ZERO_AMOUNT_ALLOWED(p)
#define SET_EXTENDED_SELECTION_SUPP(p)          (p).extendedSelectionSupport    = SET; SET_EXIST_EXTENDED_SELECTION_SUPP(p)

#define RESET_STATUS_CHECK(p)                   (p).statusCheck                 = RESET; SET_EXIST_STATUS_CHECK(p)
#define RESET_ZERO_AMOUT_ALLOWED(p)             (p).zeroAmountAllowed           = RESET; SET_EXIST_ZERO_AMOUNT_ALLOWED(p)
#define RESET_EXTENDED_SELECTION_SUPP(p)        (p).extendedSelectionSupport    = RESET; SET_EXIST_EXTENDED_SELECTION_SUPP(p)

#define IS_STATUS_CHECK(p)                      ((p).statusCheck                == SET)
#define IS_ZERO_AMOUT_ALLOWED(p)                ((p).zeroAmountAllowed          == SET)
#define IS_EXTENDED_SELECTION_SUPP(p)           ((p).extendedSelectionSupport   == SET)


//--------------------------------------------------------------------

typedef struct {
    char    aid[16];
    char    kid;
    int     configIndex;
} Aid_Kid, *Aid_KidPtr;


EpConfigPtr findConfigByAidKid(const char* aid, char kid);
int addConfigByAidKid(const char* aid, unsigned char kid, EpConfig);
int resetAllConfigs();
int loadConfigs(const char* configFolder);

//- Testing purposes
// TODO
int t_getAidKidCount();
int t_getEpConfigCount();
Aid_KidPtr t_getAidKid();
EpConfigPtr t_getEpConfig();

//--------------------------------------------------------------------







#define MAX_EP_CONFIG   20
typedef struct {
    int         count;
    EpConfig    configs[MAX_EP_CONFIG];
} EpConfigs, *EpConfigsPtr;

int addEpConfig(EpConfigsPtr configs, EpConfig config);
int resetEpConfigs(EpConfigsPtr configs);
int fillEpConfigs();



#endif// _EP_CONFIG_H_
