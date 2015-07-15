/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#ifndef MODULAR_SRC_ENTRYPOINT_EPCOMBINATIONSELECTION_H_
#define MODULAR_SRC_ENTRYPOINT_EPCOMBINATIONSELECTION_H_

#include "./epCommon.h"
/*-----------------------------------------------------------------------------
    Book B p.22
    Table 3-3
*/
#define GET_APP_PRIORITY_INDICATOR(v) ((v) & 0x0F)

/*-----------------------------------------------------------------------------
    Book B p.23
    Table 3-4
*/

typedef enum {
    Step1 = 1,
    Step2,
    Step3,
    StepExit
} Steps;


int epCombinationSelection(EpPtr pEp);
int _3_3_2_1(EpPtr pEp);
int _step1(EpPtr pEp);
int _step2(EpPtr pEp);
int _step3(EpPtr pEp);

int epFinalCombinationSelection(EpPtr pEp);

int useDefaultKernelId(const unsigned char* aid, int aidLen);
int _3_3_2_5(EpPtr pEp);

//- Testing purposes
int t_getNextStep();
void t_setNextStep(Steps s);

#endif// MODULAR_SRC_ENTRYPOINT_EPCOMBINATIONSELECTION_H_
