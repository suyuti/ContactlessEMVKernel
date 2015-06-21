#include "epPreProcessing.h"
#include "epTrnxParameters.h"
#include "../Base/err.h"
#include "./epCommon.h"

#include "epConfigHelper.h"

int epPreProcessing(EpPtr epObj)
{
    int err;

    err = 

    err = _3_1_1_1(&epObj->epConfigs, epObj->configFolder);
    err = _3_1_1_2();
    err = _3_1_1_3();
    err = _3_1_1_4();
    err = _3_1_1_5();
    err = _3_1_1_6();
    err = _3_1_1_7();
    err = _3_1_1_8();
    err = _3_1_1_9();
    err = _3_1_1_10();
    err = _3_1_1_11();
    err = _3_1_1_12();
    err = _3_1_1_13();

    epIndicators_reset();
    //updateEpTrnxParameters(EpTrnxParamsPtr p, HalInterfacesPtr pHal);

    CARD_OPEN(&gEp.hal);
    CARD_RESET(&gEp.hal);
    
    return SUCCESS;
}

//----------------------------------------------------------------------------------------------------
/**
    For each Combination, Entry Point shall reset the Entry Point
    Pre-Processing Indicators as defined in Table 5-3 of Book A
    (Entry Point Pre-Processing Indicators) to 0.
**/
int _3_1_1_1(EpConfigsPtr epConfigs, const char* configFolder) 
{ 
    int err;// = resetEpConfig(epConfigs);
   // char configFileName[120] = {0x00};
    //sprintf(configFileName, "%s/config.txt", configFolder);
    //loadConfigs(configFileName);
    //readConfig(configFileName, (EpConfigPtr)0);

    return err;
}
//----------------------------------------------------------------------------------------------------
int _3_1_1_2() { return SUCCESS;}
//----------------------------------------------------------------------------------------------------
int _3_1_1_3() { return SUCCESS;}
//----------------------------------------------------------------------------------------------------
int _3_1_1_4() { return SUCCESS;}
//----------------------------------------------------------------------------------------------------
int _3_1_1_5() { return SUCCESS;}
//----------------------------------------------------------------------------------------------------
int _3_1_1_6() { return SUCCESS;}
//----------------------------------------------------------------------------------------------------
int _3_1_1_7() { return SUCCESS;}
//----------------------------------------------------------------------------------------------------
int _3_1_1_8() { return SUCCESS;}
//----------------------------------------------------------------------------------------------------
int _3_1_1_9() { return SUCCESS;}
//----------------------------------------------------------------------------------------------------
int _3_1_1_10() { return SUCCESS;}
//----------------------------------------------------------------------------------------------------
int _3_1_1_11() { return SUCCESS;}
//----------------------------------------------------------------------------------------------------
int _3_1_1_12() { return SUCCESS;}
//----------------------------------------------------------------------------------------------------
int _3_1_1_13() { return SUCCESS;}
//----------------------------------------------------------------------------------------------------
