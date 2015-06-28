#include <stdlib.h>
#include <string.h>
#include "./epCombinationSelection.h"
#include "./epIndicators.h"
#include "../Base/err.h"
#include "../Base/general.h"


static Steps                gsNextStep;
static CandidateListItem    gsSelectedApp;

//-----------------------------------------------------------------------------

int epCombinationSelection(EpPtr pEp)
{
    if (!pEp) return NULL_PARAMETER;
    int err;

    gsNextStep = Step1;

    while(gsNextStep != StepExit) {
        switch(gsNextStep) {
            case Step1:
                err = _step1(pEp);
            break;
            case Step2:
                err = _step2(pEp);
            break;
            case Step3:
                err = _step3(pEp);
            break;
        }
    }
    return err;
}

/*---------------------------------------------
    Book B v2.5 p.32
    3.3.3
    
*/

int epFinalCombinationSelection(EpPtr pEp) 
{
    /*
        Book B v2.5 p.32
        3.3.3.1

        If there is only one Combination in the Candidate List,
        then Entry Point shall select the Combination.
    */
    if (pEp->candidateListCount == 1) {

    }
    else if (pEp->candidateListCount > 1) {
        int i              = 0;
        int maxPriority    = 0;
        int curentPriority = 0;
        for (i = 0; i < pEp->candidateListCount; ++i) {
            curentPriority =  getApplicationPriority(&(pEp->candidateList[i]));
            if (curentPriority > maxPriority) {
                gsSelectedApp = pEp->candidateList[i];
                maxPriority = curentPriority;
            }
        }

        //int err = se
    }

}

//-----------------------------------------------------------------------------

int _step1(EpPtr pEp)
{
    if (!pEp) return NULL_PARAMETER;

    int i = 0;
    int err = selectPpse(&(pEp->fci));
    if (err == SW_NOT_FOUND) return err;

    if (getLastSw() == MAKEWORD(0x90, 0x00)) {
        clearCandidateList(pEp->candidateList, MAX_CANDIDATE_LIST);
        CandidateListItem item;
        for(i = 0; i < pEp->fci._fciIssDataCount; ++i) {
            fciToCandidateItem(&(pEp->fci._fciIssData[i]), &item);
            addCandidateList(pEp->candidateList,
                            &(pEp->candidateListCount),
                            MAX_CANDIDATE_LIST,
                            &item);
        }
        gsNextStep = Step2;
    }
    else {
        gsNextStep = Step3;
    }
    return err;
}

//-----------------------------------------------------------------------------

int _step2(EpPtr pEp) 
{
    int err = SUCCESS;
    if (!pEp) return NULL_PARAMETER;

    /*
        Book B v2.5 p.27
        3.3.2.4

        IF      there is no Directory Entry (Tag '61') in the FCI,
        THEN    Entry Point shall add no Combinations to the Candidate List
                and shall proceed to Step 3.
    */
    if (pEp->fci._fciIssDataCount == 0) {
        gsNextStep = Step3;
    }

    /*
        Book B v2.5 p.27
        3.3.2.5

    */
    int i = 0;
    int j = 0;
    EpConfigPtr pConfig = NULL;
    unsigned char matchingAid[30] = {0x00};
    int selectetKernelId = 0;

    for (i = 0; i < pEp->epConfigsCount; ++i) {
        pConfig = &(pEp->epConfigs[i]);
        if (!IS_EPIND_CLESS_APP_NOT_ALLOWED(pConfig->indicators)) {
            for (j = 0; j < pEp->fci._fciIssDataCount; ++j) {
                //---------------------
                // Ref: A
                if (!isAdfNameExist(&(pEp->fci), j) ||
                    !isAdfNameValid(&(pEp->fci), j)) {
                    continue;

                }

                //---------------------
                // Ref: B
                if ((getAdfNameLen(&(pEp->fci), j) == getEpConfigAidLen(pConfig)) ||
                    startsWith(getAdfName(&(pEp->fci), j),
                               pConfig->aid) == TRUE) {
                    strncpy(matchingAid, pConfig->aid, getEpConfigAidLen(pConfig));
                }
                else {
                    continue;
                }

                //---------------------
                // Ref: C
                if (!isKernelIdExist(&(pEp->fci), j)) {
                }
                else {

                }
            }
            gsNextStep = Step3;
        }
    }
    return err;
}

//-----------------------------------------------------------------------------

int _step3(EpPtr pEp) 
{
    int err = SUCCESS;
    if (!pEp) return NULL_PARAMETER;
    return err;
}

//-----------------------------------------------------------------------------

int _3_3_1_1()
{
    /*
        Book B v2.5 p.22
        3.3.1.1

        The coding of the Application Priority Indicator is indicated in Table 3-3.
        
        IF      The Application Priority Indicator is absent from a Directory Entry,
        THEN    Entry Point shall assume b4-b1 to have a value of 0000b.    
    */

    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_3_2_1(EpPtr pEp)
{
    /*
        Book B v2.5 p.26
        3.3.2.1

        IF      Entry Point is activated by the reader at Start B,
        THEN:
            -   IF       Issuer Authentication Data and/or Issuer Script is present,
                THEN     processing shall continue at requirement 3.3.3.3 of Final
                         Combination Selection with the Combination that was
                         selected during the previous Final Combination Selection.
            - OTHERWISE, Entry Point shall perform steps 1 to 3.

        ELSE IF Entry Point is activated by the reader at Start C,
        THEN    processing shall continue at Step 3.
    */
    if (!pEp) return NULL_PARAMETER;

    if (pEp->startedByReader) {

    }
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_3_2_2(EpPtr pEp)
{
    if (!pEp) return NULL_PARAMETER;

    int err = selectPpse(&(pEp->fci));

    return err;
}

//-----------------------------------------------------------------------------

int _3_3_2_3()
{
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_3_2_4()
{
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_3_2_5()
{
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_3_2_6()
{
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_3_2_7()
{
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_3_3_1()
{
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_3_3_2()
{
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_3_3_3()
{
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_3_3_4()
{
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_3_3_5()
{
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_3_3_6()
{
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_3_3_7()
{
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int t_getNextStep() 
{
    return gsNextStep;
}

void t_setNextStep(Steps s) 
{
    gsNextStep = s;
}