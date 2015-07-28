/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "./epCombinationSelection.h"
#include "./epIndicators.h"
#include "../Common/err.h"
#include "../Common/general.h"
#include "../Common/utils.h"
#include "../Emv/fci.h"
#include "./epConfig.h"
#include "../Common/aid.h"
#include "epCommon.h"
// #include "../Base/kernels.h"


static Steps                gsNextStep = Step1;
static CandidateListItem    gsSelectedApp;
static unsigned char        gsMatchingAid[30]  = {0x00};
static int                  gsMatchingAidLen   = 0;
static DefaulKernelIds      gsRequestedKernelId = OtherDefaultKernelId;

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
            case StepExit:
                return err;
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
    } else if (pEp->candidateListCount > 1) {
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

        // int err = se
    }
    return SUCCESS;
}

//-----------------------------------------------------------------------------
/*
 * 3.3.2.2
 * Entry Point shall send a SELECT (PPSE) command (as described in [EMV 4.2 Book 1], section 11.3.2)
 * to the card, with a file name of ‘2PAY.SYS.DDF01’.
 *
 * 3.3.2.3
 * IF         Entry Point receives SW1 SW2 = '9000' in response to the SELECT (PPSE) command,
 * THEN       Entry Point shall proceed to Step 2.
 * OTHERWISE, Entry Point shall add no Combinations to the
 *            Candidate List and shall proceed to Step 3.
 *
 * */

int _step1(EpPtr pEp)
{
    if (!pEp) return NULL_PARAMETER;

    // 3.3.2.2
    int err = selectPpse(&(pEp->fci));
    if (err == SW_NOT_FOUND) return err;

    // 3.3.2.3
    if (getLastSw() == MAKEWORD(0x90, 0x00)) {
        gsNextStep = Step2;
    } else {
        gsNextStep = Step3;
    }
    return SUCCESS;
}

//-----------------------------------------------------------------------------
/*
 * 3.3.2.4
 * 3.3.2.5 A,B,C,D
 *
 * */

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
    if (pEp->fci._directoryEntryCount == 0) {
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

    // 3.3.2.6
    if (pEp->candidateListCount >= 1) {
        // TODO
        err = epFinalCombinationSelection(pEp);
    } else {
        // 3.3.2.7
        // TODO
        gsNextStep = StepExit;
    }

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
        if (FALSE) {
        } else {
            gsNextStep = Step1;
        }
    } else if (pEp->startPoint == StartedAtC) {
        gsNextStep = Step3;
    }
    return SUCCESS;
}

//-----------------------------------------------------------------------------

DefaulKernelIds useDefaultKernelId(const unsigned char* aid, int aidLen)
{
    // TODO ...
    int i = 0;
    for(i = 0; i < KernelRidTypesCount; ++i) {
        if (memcmp(aid, gKernelRids[i].rid, 5) == 0) {
            return gKernelRids[i].defaultKernelId;
        }
    }
    return OtherDefaultKernelId;  // DefultKernel
}

//-----------------------------------------------------------------------------

int _3_3_2_5(EpPtr pEp)
{
    EpConfigPtr         pConfig          = NULL;
    int                 i                = 0;
    int                 j                = 0;
    DirectoryEntryPtr   directoryEntry   = NULL;

    memset(gsMatchingAid, 0x00, sizeof(gsMatchingAid));
    gsMatchingAidLen = 0;
    gsRequestedKernelId = OtherDefaultKernelId;

    for (i = 0; i < pEp->epConfigsCount; ++i) {
        pConfig = &(pEp->epConfigs[i]);
        if (!IS_EPIND_CLESS_APP_NOT_ALLOWED(pConfig->indicators)) {
            for (j = 0; j < pEp->fci._directoryEntryCount; ++j) {
                directoryEntry = &(pEp->fci._directoryEntry[j]);

                // 3.3.2.5 A
                if (!isAdfNameExist(directoryEntry) ||
                    !isAdfNameValid(directoryEntry)) {
                    continue;
                }

                // 3.3.2.5 B
                int cardAdfNameLen = getAdfNameLen(directoryEntry);
                int termAidLen = getEpConfigAidLen(pConfig);

                if (cardAdfNameLen == termAidLen) {
                    // Full match
                    memcpy(gsMatchingAid, pConfig->aid, getEpConfigAidLen(pConfig)+1);
                    gsMatchingAidLen = getEpConfigAidLen(pConfig);
                }
                else if (cardAdfNameLen > termAidLen) {
                    if (startsWith((const char*)getAdfName(directoryEntry), pConfig->aid+1) == TRUE) {
                        // Partial match
                        memcpy(gsMatchingAid, pConfig->aid, getEpConfigAidLen(pConfig)+1);
                        gsMatchingAidLen = getEpConfigAidLen(pConfig);
                    }
                    else {
                        continue;
                    }
                }
                else {
                    continue;
                }
/*

                if ((getAdfNameLen(directoryEntry) == getEpConfigAidLen(pConfig))
                     ||
                    startsWith((const char*)getAdfName(directoryEntry), pConfig->aid) == TRUE) {
                    // TODO
                    // strncpy(matchingAid, pConfig->aid, getEpConfigAidLen(pConfig));
                } else {
                    continue;
                }
*/
                // 3.3.2.5 C
                if (isKernelIdExist(directoryEntry) == FALSE) {
                    gsRequestedKernelId = useDefaultKernelId(gsMatchingAid+1, gsMatchingAidLen);
                } else {

                    if ((CHECK_BIT(directoryEntry->_9F2A[1], BIT_8) == RESET &&
                         CHECK_BIT(directoryEntry->_9F2A[1], BIT_7) == RESET) ||
                        (CHECK_BIT(directoryEntry->_9F2A[1], BIT_8) == RESET &&
                         CHECK_BIT(directoryEntry->_9F2A[1], BIT_7) == SET)) {
                        gsRequestedKernelId = directoryEntry->_9F2A[1];
                    }
                    else if ((CHECK_BIT(directoryEntry->_9F2A[1], BIT_8) == SET &&
                              CHECK_BIT(directoryEntry->_9F2A[1], BIT_7) == RESET) ||
                             (CHECK_BIT(directoryEntry->_9F2A[1], BIT_8) == SET &&
                              CHECK_BIT(directoryEntry->_9F2A[1], BIT_7) == SET)) {
                        if (directoryEntry->_9F2A[0] < 3) {
                            continue;
                        }
                        if (getShortKernelId(directoryEntry) != 0x00) {
                            // TODO
                        }
                        else {
                            // TODO
                        }
                    }
                }

                // 3.3.2.5 D
                if (gsRequestedKernelId == 0x00) {
                    // TODO
                } else {
                    // TODO
                    if (gsRequestedKernelId == getKernelId(directoryEntry)) {
                    } else {
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

//-----------------------------------------------------------------------------

unsigned char* t_getMatchingAid()
{
    return gsMatchingAid;
}

//-----------------------------------------------------------------------------

int t_getMatchingAidLen()
{
    return gsMatchingAidLen;
}

//-----------------------------------------------------------------------------

DefaulKernelIds t_getRequestedKernelId()
{
    return gsRequestedKernelId;
}
