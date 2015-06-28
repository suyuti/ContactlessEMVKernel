#include <stdlib.h>
#include <string.h>
#include "./epCombinationSelection.h"
#include "./epIndicators.h"
#include "../Base/err.h"
#include "../Base/general.h"
#include "../Base/kernels.h"


static Steps                gsNextStep;
static CandidateListItem    gsSelectedApp;

//-----------------------------------------------------------------------------

int epCombinationSelection(EpPtr pEp)
{
    if (!pEp) return NULL_PARAMETER;
    int err;

    gsNextStep = Step1;
    err = _3_3_2_1(pEp);
    IS_SUCCESS(err);

    while (gsNextStep != StepExit) {
        switch (gsNextStep) {
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

    int err = selectPpse(&(pEp->fci));
    if (err == SW_NOT_FOUND) return err;

    if (getLastSw() == MAKEWORD(0x90, 0x00)) {
        gsNextStep = Step2;
    }
    else {
        gsNextStep = Step3;
    }
    return SUCCESS;
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
        return SUCCESS;
    }


    err = _3_3_2_5(pEp);

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

    if (pEp->startPoint == StartedAtB) {
        // TODO
    }
    else if (pEp->startPoint == StartedAtC) {
        gsNextStep = Step1;
    }
    else {
        gsNextStep = Step3;
    }
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int useDefaultKernelId(const unsigned char* aid, int aidLen)
{
    // TODO ...
    return DefultKernel_AmericanExpress;
}

//-----------------------------------------------------------------------------

int _3_3_2_5(EpPtr pEp)
{
    EpConfigPtr         pConfig          = NULL;
    int                 i                = 0;
    int                 j                = 0;
    FciIssDataPtr       directoryEntry   = NULL;
    int                 requestedKernelId = 0xFF;
    unsigned char       matchingAid[30]  = {0x00};
    int                 matchingAidLen   = 0;

    for (i = 0; i < pEp->epConfigsCount; ++i) {
        pConfig = &(pEp->epConfigs[i]);
        if (!IS_EPIND_CLESS_APP_NOT_ALLOWED(pConfig->indicators)) {
            for (j = 0; j < pEp->fci._fciIssDataCount; ++j) {
                directoryEntry = &(pEp->fci._fciIssData[j]);

                // 3.3.2.5 A
                if (!isAdfNameExist(directoryEntry) ||
                    !isAdfNameValid(directoryEntry)) {
                    continue;
                }

                // 3.3.2.5 B
                if ((getAdfNameLen(directoryEntry) == getEpConfigAidLen(pConfig)) 
                     ||
                    startsWith(getAdfName(directoryEntry), pConfig->aid) == TRUE) {
                    // TODO
                    //strncpy(matchingAid, pConfig->aid, getEpConfigAidLen(pConfig));
                }
                else {
                    continue;
                }

                // 3.3.2.5 C
                if (isKernelIdExist(directoryEntry) == FALSE) {
                    requestedKernelId = useDefaultKernelId(matchingAid, matchingAidLen);
                }
                else {
                    if (getKernelIdLen(directoryEntry) == 0) {  // ? size = 0 means KernelId doesn't exist.
                        requestedKernelId = useDefaultKernelId(matchingAid, matchingAidLen);
                        //return SUCCESS;
                        // TODO
                    }
                    switch(getKernelType(directoryEntry)) {
                        case RfuKernel:
                        case InternationalKernel:
                            requestedKernelId = getShortKernelId(directoryEntry);
                        break;
                        case DomesticKernelEmvCoFormat:
                        case DomesticKernelPropFormat: {
                            // TODO p.29
                            if (getShortKernelId(directoryEntry) != 0x00) {
                                // TODO
                            }
                            else {
                                // TODO
                            }
                        }
                        break;
                    }
                }

                // 3.3.2.5 D
                if (requestedKernelId == 0x00) {
                    // TODO
                }
                else {
                    // TODO
                    if (requestedKernelId == getKernelId(directoryEntry)) {

                    }
                    else {
                        continue;
                    }
                }

                // 3.3.2.5 E
                CandidateListItem item;

                fciToCandidateItem(directoryEntry, &item);
                addCandidateList(pEp->candidateList,
                                &(pEp->candidateListCount),
                                MAX_CANDIDATE_LIST,
                                &item);

            }
        }
    }
    gsNextStep = Step3;

    return SUCCESS;
}

//-----------------------------------------------------------------------------

int t_getNextStep() 
{
    return gsNextStep;
}

//-----------------------------------------------------------------------------

void t_setNextStep(Steps s) 
{
    gsNextStep = s;
}