/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */
#include <memory.h>
#include "epProtocolActivation.h"
#include "../Common/err.h"
#include "./epIndicators.h"
#include "epCommon.h"
#include "../Common/general.h"

//-----------------------------------------------------------------------------

int epProtocolActivation(EpPtr p)
{
    if (!p) return NULL_PARAMETER;

    int err = _3_2_1_1(p);
    if (err != SUCCESS) return err;

    err = _3_2_1_2(p);
    if (err != SUCCESS) return err;

    err = _3_2_1_3(p);
    if (err != SUCCESS) return err;

    err = _3_2_1_4(p);
    if (err != SUCCESS) return err;

    err = _3_2_1_5(p);
    if (err != SUCCESS) return err;

    err = _3_2_1_6(p);
    if (err != SUCCESS) return err;

    return err;
}

//-----------------------------------------------------------------------------

int _3_2_1_1(EpPtr pEp)
{
    /*
        Book B v2.5 p.17
        3.2.1.1

        IF the Restart flag is 0,
        THEN:
            -   IF      Entry Point is activated by the reader4 at Start B,
                THEN:
                        o For each Combination, Entry Point shall reset the Entry
                          Point Pre-Processing Indicators to 0.
                        o For each Combination,
                            IF      Terminal Transaction Qualifiers (TTQ) is configured,
                            THEN    Entry Point shall copy the TTQ from Entry Point
                                    Configuration Data (see Book A, Table 5-2) into the
                                    Copy of TTQ in the Entry Point Pre-Processing Indicators.
                - Entry Point shall clear the Candidate List.

    */
    int i = 0;
    if (!pEp) return NULL_PARAMETER;

    if (pEp->restartFlag == RESET) {
        if (pEp->startPoint == StartedAtB) {
            for (i = 0; i < pEp->epConfigsCount; ++i) {
                epIndicators_reset(&(pEp->epConfigs[i].indicators));

                // TODO: if ttq configured
                memcpy(pEp->epConfigs[i].indicators.ttq, pEp->epConfigs[i].configData.ttq, 4);  // TODO magic number
            }
        }

        clearCandidateList(pEp->candidateList, MAX_CANDIDATE_LIST);
        pEp->candidateListCount = 0;  // TODO, counter resetting should be in helper function
    }

    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_2_1_2(EpPtr pEp)
{
    /*
        Book B v2.5 p.18
        3.2.1.2

        IF      the Restart flag is 1,
        AND     the value of the retained UI Request on Restart Present
                parameter is 'Yes',
        THEN    Entry Point shall send the retained User Interface Request.
        OTHERWISE (the Restart flag is 0 or the value of the retained
                UI Request on Restart Present parameter is 'No'), Entry Point shall
                send a User Interface Request with the following parameters:
                - Message Identifier: '15' (“Present Card”)
                - Status: Ready to Read
    */

    if (!pEp) return NULL_PARAMETER;
    if (pEp->restartFlag == SET &&
        pEp->outcome.uiRequestOnRestartPresent == YES) {
        // TODO
    }
    else {
        // TODO
    }

    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_2_1_3(EpPtr pEp)
{
    /*
        Book B v2.5 p.18
        3.2.1.3

        The field shall be powered up and polling performed as defined in
        the Main Loop of Book D.    
    */
    if (!pEp) return  NULL_PARAMETER;
    // TODO
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_2_1_4(EpPtr pEp)
{
    /*
        Book B v2.5 p.18
        3.2.1.4

        IF      A collision as defined in Book D is reported to Entry Point,
        THEN    Entry Point shall send a User Interface Request with the
                following parameters:
                - Message Identifier: '19' (“Please Present One Card Only”)
                - Status: Contactless collision detected (Processing Error)    
    */
    if (!pEp) return  NULL_PARAMETER;
    // TODO
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_2_1_5(EpPtr pEp)
{
    /*
        Book B v2.5 p.18
        3.2.1.5

        WHEN    The collision condition is no longer indicated,
        THEN    Entry Point shall send a User Interface Request with the
                following parameters:
                - Message Identifier: '19' (“Please Present One Card Only”)
                - Status: Ready to Read    
    */
    if (!pEp) return  NULL_PARAMETER;
    // TODO
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_2_1_6(EpPtr pEp)
{
    /*
        Book B v2.5 p.18
        3.2.1.6

        As described in Book D requirement 6.4.1.12, Entry Point shall not
        use a higher layer command in the Higher layer - INF field of the
        ATTRIB command.
    */
    if (!pEp) return  NULL_PARAMETER;
    // TODO
    return SUCCESS;
}

//-----------------------------------------------------------------------------
