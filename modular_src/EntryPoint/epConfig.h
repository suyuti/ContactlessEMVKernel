/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#ifndef MODULAR_SRC_ENTRYPOINT_EPCONFIG_H_
#define MODULAR_SRC_ENTRYPOINT_EPCONFIG_H_

#include "../Common/general.h"
#include "./epCommon.h"
#include "../Common/bits.h"

int loadConfigs(EpPtr pEp);

int clearEpConfigData(EpConfigDataPtr obj);
int clearEpConfigs(EpPtr pEp);

int addEpConfig(EpPtr pEp, EpConfig config);
int findEpConfig(EpPtr pEp, const char* aid, unsigned char kid, EpConfigPtr obj);

int getEpConfigAidLen(EpConfigPtr p);
unsigned char* getEpConfigAid(EpConfigPtr p);

int parseEpconfig(EpConfigDataPtr obj, const char* line);
int getEpConfigAidLen(EpConfigPtr p);


#define STATUS_CHECK_BIT                        1
#define ZERO_AMOUT_ALLOWED_BIT                  2
#define CLESS_TRNX_LIMIT_BIT                    3
#define CLESS_FLOOR_LIMIT_BIT                   4
#define TERM_FLOOR_LIMIT_BIT                    5
#define CVM_REQ_BIT                             6
#define TTQ_BIT                                 7
#define EXTENDED_SELECTION_SUPP_BIT             8


#define IS_EXIST_STATUS_CHECK(p)                CHECK_BIT((p).bitmap, STATUS_CHECK_BIT              )
#define IS_EXIST_ZERO_AMOUNT_ALLOWED(p)         CHECK_BIT((p).bitmap, ZERO_AMOUT_ALLOWED_BIT        )
#define IS_EXIST_CLESS_TRNX_LIMIT(p)            CHECK_BIT((p).bitmap, CLESS_TRNX_LIMIT_BIT          )
#define IS_EXIST_CLESS_FLOOR_LIMIT(p)           CHECK_BIT((p).bitmap, CLESS_FLOOR_LIMIT_BIT         )
#define IS_EXIST_TERM_FLOOR_LIMIT(p)            CHECK_BIT((p).bitmap, TERM_FLOOR_LIMIT_BIT          )
#define IS_EXIST_CVM_REQ_LIMIT(p)               CHECK_BIT((p).bitmap, CVM_REQ_BIT                   )
#define IS_EXIST_TTQ(p)                         CHECK_BIT((p).bitmap, TTQ_BIT                       )
#define IS_EXIST_EXTENDED_SELECTION_SUPP(p)     CHECK_BIT((p).bitmap, EXTENDED_SELECTION_SUPP_BIT   )

#define SET_EXIST_STATUS_CHECK(p)               SET_BIT((p).bitmap, STATUS_CHECK_BIT              )
#define SET_EXIST_ZERO_AMOUNT_ALLOWED(p)        SET_BIT((p).bitmap, ZERO_AMOUT_ALLOWED_BIT        )
#define SET_EXIST_CLESS_TRNX_LIMIT(p)           SET_BIT((p).bitmap, CLESS_TRNX_LIMIT_BIT          )
#define SET_EXIST_CLESS_FLOOR_LIMIT(p)          SET_BIT((p).bitmap, CLESS_FLOOR_LIMIT_BIT         )
#define SET_EXIST_TERM_FLOOR_LIMIT(p)           SET_BIT((p).bitmap, TERM_FLOOR_LIMIT_BIT          )
#define SET_EXIST_CVM_REQ_LIMIT(p)              SET_BIT((p).bitmap, CVM_REQ_BIT                   )
#define SET_EXIST_TTQ(p)                        SET_BIT((p).bitmap, TTQ_BIT                       )
#define SET_EXIST_EXTENDED_SELECTION_SUPP(p)    SET_BIT((p).bitmap, EXTENDED_SELECTION_SUPP_BIT   )

#define RESET_EXIST_STATUS_CHECK(p)             RESET_BIT((p).bitmap, STATUS_CHECK_BIT              )
#define RESET_EXIST_ZERO_AMOUNT_ALLOWED(p)      RESET_BIT((p).bitmap, ZERO_AMOUT_ALLOWED_BIT        )
#define RESET_EXIST_CLESS_TRNX_LIMIT(p)         RESET_BIT((p).bitmap, CLESS_TRNX_LIMIT_BIT          )
#define RESET_EXIST_CLESS_FLOOR_LIMIT(p)        RESET_BIT((p).bitmap, CLESS_FLOOR_LIMIT_BIT         )
#define RESET_EXIST_TERM_FLOOR_LIMIT(p)         RESET_BIT((p).bitmap, TERM_FLOOR_LIMIT_BIT          )
#define RESET_EXIST_CVM_REQ_LIMIT(p)            RESET_BIT((p).bitmap, CVM_REQ_BIT                   )
#define RESET_EXIST_TTQ(p)                      RESET_BIT((p).bitmap, TTQ_BIT                       )
#define RESET_EXIST_EXTENDED_SELECTION_SUPP(p)  RESET_BIT((p).bitmap, EXTENDED_SELECTION_SUPP_BIT   )


#define SET_STATUS_CHECK(p)                     SET_EXIST_STATUS_CHECK(p);              (p).statusCheck       = SET
#define SET_ZERO_AMOUT_ALLOWED(p)               SET_EXIST_ZERO_AMOUNT_ALLOWED(p);       (p).zeroAmountAllowed = SET
#define SET_CLESS_TRNX_LIMIT(p, l)              SET_EXIST_CLESS_TRNX_LIMIT(p);          (p).clessTrnxLimit     = (l)
#define SET_CLESS_FLOOR_LIMIT(p, l)             SET_EXIST_CLESS_FLOOR_LIMIT(p);         (p).clessFloorLimit    = (l)
#define SET_TERM_FLOOR_LIMIT(p, l)              SET_EXIST_TERM_FLOOR_LIMIT(p);          (p).termFloorLimit     = (l)
#define SET_CVM_REQ_LIMIT(p, l)                 SET_EXIST_CVM_REQ_LIMIT(p);             (p).cvmRequiredLimit   = (l)
#define SET_TTQ(p, val4)                        SET_EXIST_TTQ(p);                       memcpy((p).ttq, (val4), 4)
#define SET_EXTENDED_SELECTION_SUPP(p)          SET_EXIST_EXTENDED_SELECTION_SUPP(p);   (p).extendedSelectionSupport = SET

#define RESET_STATUS_CHECK(p)                   SET_EXIST_STATUS_CHECK(p);              (p).statusCheck        = RESET
#define RESET_ZERO_AMOUT_ALLOWED(p)             SET_EXIST_ZERO_AMOUNT_ALLOWED(p);       (p).zeroAmountAllowed  = RESET
#define RESET_CLESS_TRNX_LIMIT(p, l)            SET_EXIST_CLESS_TRNX_LIMIT(p);          (p).clessTrnxLimit     = 0
#define RESET_CLESS_FLOOR_LIMIT(p, l)           SET_EXIST_CLESS_FLOOR_LIMIT(p);         (p).clessFloorLimit    = 0
#define RESET_TERM_FLOOR_LIMIT(p, l)            SET_EXIST_TERM_FLOOR_LIMIT(p);          (p).termFloorLimit     = 0
#define RESET_CVM_REQ_LIMIT(p, l)               SET_EXIST_CVM_REQ_LIMIT(p);             (p).cvmRequiredLimit   = 0
#define RESET_TTQ(p, val4)                      SET_EXIST_TTQ(p);                       memset((p).ttq, 0x00, 4)
#define RESET_EXTENDED_SELECTION_SUPP(p)        SET_EXIST_EXTENDED_SELECTION_SUPP(p);   (p).extendedSelectionSupport = RESET

#define IS_STATUS_CHECK(p)                      (CHECK_BIT((p).bitmap, STATUS_CHECK_BIT         ) && ((p).statusCheck       == SET))
#define IS_ZERO_AMOUT_ALLOWED(p)                (CHECK_BIT((p).bitmap, ZERO_AMOUT_ALLOWED_BIT   ) && ((p).zeroAmountAllowed == SET))
// #define IS_CLESS_TRNX_LIMIT(p, l)               (CHECK_BIT((p).bitmap, CLESS_TRNX_LIMIT_BIT       ) && ((p).clessTrnxLimit      == SET))
// #define IS_CLESS_FLOOR_LIMIT(p, l)              (CHECK_BIT((p).bitmap, CLESS_FLOOR_LIMIT_BIT      ) && ((p).clessFloorLimit     == SET))
// #define IS_TERM_FLOOR_LIMIT(p, l)               (CHECK_BIT((p).bitmap, TERM_FLOOR_LIMIT_BIT       ) && ((p).termFloorLimit      == SET))
// #define IS_CVM_REQ_LIMIT(p, l)                  (CHECK_BIT((p).bitmap, CVM_REQ_BIT                ) && ((p).cvmReqLimit         == SET))
// #define IS_TTQ(p, val4)                         (CHECK_BIT((p).bitmap, TTQ_BIT                    ) && ((p).ttq == SET))
#define IS_EXTENDED_SELECTION_SUPP(p)           (CHECK_BIT((p).bitmap, EXTENDED_SELECTION_SUPP_BIT) && ((p).extendedSelectionSupport == SET))



//--------------------------------------------------------------------
/*
typedef struct {
    char    aid[16];
    char    kid;
    int     configIndex;
} Aid_Kid, *Aid_KidPtr;


EpConfigDataPtr findConfigByAidKid(const char* aid, char kid);
int addConfigByAidKid(const char* aid, unsigned char kid, EpConfigData);
int resetAllConfigs();
int loadConfigs(const char* configFolder);
int getConfigCount(EpConfigDataPtr pConfigList);

//- Testing purposes
// TODO
int t_getAidKidCount();
int t_getEpConfigCount();
Aid_KidPtr t_getAidKid();
EpConfigPtr t_getEpConfig();

//--------------------------------------------------------------------




*/

/*
#define MAX_EP_CONFIG   20
typedef struct {
    int             count;
    EpConfig        configs[MAX_EP_CONFIG];
} EpConfigs, *EpConfigsPtr;

int addEpConfig(EpConfigsPtr configs, EpConfig config);
int resetEpConfigs(EpConfigsPtr configs);
int fillEpConfigs();
*/


#endif  // MODULAR_SRC_ENTRYPOINT_EPCONFIG_H_
