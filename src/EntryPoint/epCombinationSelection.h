#ifndef _EPCOMBINATION_SELECTION_H_
#define _EPCOMBINATION_SELECTION_H_

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


int epCombinationSelection();

int _step1(EpPtr pEp);
int _step2(EpPtr pEp);

//- Testing purposes
int t_getNextStep();
void t_setNextStep(Steps s);







int _3_3_1_1();

int _3_3_2_1();
int _3_3_2_2(EpPtr pEp);
int _3_3_2_3();
int _3_3_2_4();
int _3_3_2_5();
int _3_3_2_6();
int _3_3_2_7();

int _3_3_3_1();
int _3_3_3_2();
int _3_3_3_3();
int _3_3_3_4();
int _3_3_3_5();
int _3_3_3_6();
int _3_3_3_7();


#endif// _EPCOMBINATION_SELECTION_H_
