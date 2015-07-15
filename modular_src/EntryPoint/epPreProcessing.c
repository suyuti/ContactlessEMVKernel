/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#include <string.h>
#include "epPreProcessing.h"
#include "epTrnxParameters.h"
#include "../Common/err.h"
#include "./epCommon.h"
#include "./epConfig.h"
#include "./ttq.h"
#include "./epIndicators.h"
#include "./epOutcome.h"

int epPreProcessing(EpPtr epObj, int amount, int amountAuthorized)
{
    int err;

    int i = 0;
    for (i = 0; i < epObj->epConfigsCount; ++i) {
        err = _3_1_1_1(&(epObj->epConfigs[i]));
        err = _3_1_1_2(&(epObj->epConfigs[i]));
        err = _3_1_1_3(&(epObj->epConfigs[i]), amount, amountAuthorized);
        err = _3_1_1_4(&(epObj->epConfigs[i]), amount, amountAuthorized);
        err = _3_1_1_5(&(epObj->epConfigs[i]), amountAuthorized);
        err = _3_1_1_6(&(epObj->epConfigs[i]), amountAuthorized);
        err = _3_1_1_7(&(epObj->epConfigs[i]), amountAuthorized);
        err = _3_1_1_8(&(epObj->epConfigs[i]), amountAuthorized);

        if (IS_EXIST_TTQ(epObj->epConfigs[i].configData)) {
            err = _3_1_1_9(&(epObj->epConfigs[i]));
            err = _3_1_1_10(&(epObj->epConfigs[i]));
            err = _3_1_1_11(&(epObj->epConfigs[i]));
            err = _3_1_1_12(&(epObj->epConfigs[i]));
        }
    }
    err = _3_1_1_13();

    return err;
}

//-----------------------------------------------------------------------------

int _3_1_1_1(EpConfigPtr pConfig)
{
    /*
        Book B v2.5 p.13
        3.1.1.1

        For each Combination, Entry Point shall reset the Entry Point
        Pre-Processing Indicators as defined in Table 5-3 of Book A
        (Entry Point Pre-Processing Indicators) to 0.
    */
    if (!pConfig) return NULL_PARAMETER;
    epIndicators_reset(&(pConfig->indicators));
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_1_1_2(EpConfigPtr pConfig)
{
    /*  Book B v2.5 p.13
        3.1.1.2
        
        Entry Point shall reset byte 2, bit 8 and 
        bit 7 in the Copy of TTQ to 00b 
        (‘Online cryptogram not required’ and 
        ‘CVM not required’).
    */
    if (!pConfig) return NULL_PARAMETER;
    if (IS_EXIST_TTQ(pConfig->configData)) {
        memcpy(pConfig->indicators.ttq,
               pConfig->configData.ttq,
               TTQ_LEN);
        RESET_ONLINE_CRYPT_REQ(pConfig->indicators.ttq);
        RESET_CVM_REQ(pConfig->indicators.ttq);
    }
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_1_1_3(EpConfigPtr pConfig, int amount, int amountAuthorized)
{
    /*
        Book B v2.5 p.13
        3.1.1.3
        IF      All of the following are true:
                    - the Status Check Support flag is present,
                    - AND the Status Check Support flag is 1,
                    - AND the Amount, Authorised is a single unit of currency,
        THEN    Entry Point shall set the ‘Status Check Requested’ indicator 
                for the Combination to 1.
    */
    if (!pConfig) return NULL_PARAMETER;

    if (IS_EXIST_STATUS_CHECK(pConfig->configData)
        && IS_STATUS_CHECK(pConfig->configData)
        // TODO &&
        ) {
        SET_EPIND_STATUS_CHECK_REQ(pConfig->indicators);
    }
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_1_1_4(EpConfigPtr pConfig, int amount, int amountAuthorized)
{
    /*
        Book B v2.5 p.13
        3.1.1.4

        IF   the value of Amount, Authorised is zero, 
        THEN
            - If the Zero Amount Allowed flag is present 
              and the Zero Amount Allowed flag is 0, then 
              Entry Point shall set the 
              ‘Contactless Application Not Allowed’ indicator 
              for the Combination to 1.
            - Otherwise, Entry Point shall set the 
              ‘Zero Amount’ indicator for the Combination to 1.
    */
    if (!pConfig) return NULL_PARAMETER;

    if (amountAuthorized == 0) {
        if (IS_EXIST_ZERO_AMOUNT_ALLOWED(pConfig->configData)
            && !IS_ZERO_AMOUT_ALLOWED(pConfig->configData)) {
            SET_EPIND_CLESS_APP_NOT_ALLOWED(pConfig->indicators);
        } else {
            SET_EPIND_ZERO_AMOUNT(pConfig->indicators);
        }
    }

    return SUCCESS;
}

//----------------------------------------------------------------------------------------------------

int _3_1_1_5(EpConfigPtr pConfig, int amountAuthorized)
{
    /*
        Book B v2.5 p.14
        3.1.1.5

        IF      the Reader Contactless Transaction Limit is present
        AND     the value of Amount, Authorised is greater than or equal to
                this limit, 
        THEN    Entry Point shall set the ‘Contactless Application Not
                Allowed’ indicator for the Combination to 1.
    */
    if (!pConfig) return NULL_PARAMETER;

    // if (IS_EXIST_CLESS_TRNX_LIMIT()) {
    // }
    return SUCCESS;
}

//----------------------------------------------------------------------------------------------------

int _3_1_1_6(EpConfigPtr pConfig, int amountAuthorized)
{
    /*
        Book B v2.5 p.14
        3.1.1.6

        IF      the Reader Contactless Floor Limit is present
        AND     the value of Amount, Authorised is greater than this limit,
        THEN    Entry Point shall set the ‘Reader Contactless Floor Limit
                Exceeded’ indicator for the Combination to 1.
    */    
    if (!pConfig) return NULL_PARAMETER;

    if (IS_EXIST_CLESS_FLOOR_LIMIT(pConfig->configData)
        && (amountAuthorized > pConfig->configData.clessFloorLimit)
        ) {
        SET_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(pConfig->indicators);
    }
    return SUCCESS;
}

//----------------------------------------------------------------------------------------------------

int _3_1_1_7(EpConfigPtr pConfig, int amountAuthorized)
{
    /*
        Book B v2.5 p.14
        3.1.1.7

        IF      All of the following are true:
                    - the Reader Contactless Floor Limit is not present,
                    - AND the Terminal Floor Limit (Tag '9F1B') is present,
                    - AND the value of Amount, Authorised is greater than the
                      Terminal Floor Limit (Tag '9F1B'),
        
        THEN    Entry Point shall set the ‘Reader Contactless Floor Limit
                Exceeded’ indicator for the Combination to 1.
    */
    if (!pConfig) return NULL_PARAMETER;

    if (!IS_EXIST_CLESS_FLOOR_LIMIT(pConfig->configData)
        && IS_EXIST_TERM_FLOOR_LIMIT(pConfig->configData)
        && (amountAuthorized > pConfig->configData.termFloorLimit)) {
        SET_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(pConfig->indicators);
    }
    return SUCCESS;
}

//----------------------------------------------------------------------------------------------------

int _3_1_1_8(EpConfigPtr pConfig, int amountAuthorized)
{
    /*
        Book B v2.5 p.14
        3.1.1.8

        IF      The Reader CVM Required Limit is present
        AND     the value of Amount, Authorised is greater than or equal to
                this limit,
        THEN    Entry Point shall set the ‘Reader CVM Required Limit
                Exceeded’ indicator for the Combination to 1
    */
    if (!pConfig) return NULL_PARAMETER;

    if (IS_EXIST_CVM_REQ_LIMIT(pConfig->configData)
        && (amountAuthorized >= pConfig->configData.cvmRequiredLimit)) {
        SET_EPIND_READER_CVM_REQ_LIMIT_EXCEEDED(pConfig->indicators);
    }
    return SUCCESS;
}

//----------------------------------------------------------------------------------------------------

int _3_1_1_9(EpConfigPtr pConfig)
{
    /*
        Book B v2.5 p.15
        3.1.1.9

        IF      the ‘Reader Contactless Floor Limit Exceeded’ indicator is 1,
        THEN    Entry Point shall set byte 2, bit 8 in the Copy of TTQ for the
                Combination to 1b (‘Online cryptogram required’).
    */
    if (!pConfig) return NULL_PARAMETER;

    if (IS_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(pConfig->indicators)) {
        SET_ONLINE_CRYPT_REQ(pConfig->indicators.ttq);
    }
    return SUCCESS;
}
//----------------------------------------------------------------------------------------------------
int _3_1_1_10(EpConfigPtr pConfig)
{
    /*
        Book B v2.5 p.15
        3.1.1.10

        IF      the ‘Status Check Requested’ indicator is 1,
        THEN    Entry Point shall set byte 2, bit 8 in the Copy of TTQ for the
                Combination to 1b (‘Online cryptogram required’).
    */
    if (!pConfig) return NULL_PARAMETER;

    if (IS_EPIND_STATUS_CHECK_REQ(pConfig->indicators)) {
        SET_ONLINE_CRYPT_REQ(pConfig->indicators.ttq);
    }
    return SUCCESS;
}
//----------------------------------------------------------------------------------------------------
int _3_1_1_11(EpConfigPtr pConfig)
{
    /*
        Book B v2.5 p.15
        3.1.1.11

        IF      the ‘Zero Amount’ indicator is 1,
        THEN:
            - IF    byte 1, bit 4 of the Copy of TTQ is 0b (‘Online capable
                    reader’),
            THEN    Entry Point shall set byte 2, bit 8 in the Copy of TTQ for
                        the Combination to 1b (‘Online cryptogram required’).
            - OTHERWISE 
                    (byte 1 bit 4 of the Copy of TTQ is 1b (‘Offline-only
                    reader’)), Entry Point shall set the ‘Contactless Application Not
                    Allowed’ indicator for the Combination to 1.
    */
    if (!pConfig) return NULL_PARAMETER;

    if (IS_EPIND_ZERO_AMOUNT(pConfig->indicators)) {
        // TODO
    }
    return SUCCESS;
}
//----------------------------------------------------------------------------------------------------
int _3_1_1_12(EpConfigPtr pConfig)
{
    /*
        Book B v2.5 p.15
        3.1.1.12

        IF      the ‘Reader CVM Required Limit Exceeded’ indicator is 1,
        THEN    Entry Point shall set byte 2, bit 7 in the Copy of TTQ for the
                Combination to 1b (‘CVM required’).
    */
    if (!pConfig) return NULL_PARAMETER;

    if (IS_EPIND_READER_CVM_REQ_LIMIT_EXCEEDED(pConfig->indicators)) {
        // TODO
    }
    return SUCCESS;
}
//----------------------------------------------------------------------------------------------------
int _3_1_1_13(EpPtr pEp)
{
    /*
        Book B v2.5 p.16
        3.1.1.13

        IF,     for all the Combinations, the ‘Contactless Application Not
                Allowed’ indicator is 1,
        THEN    Entry Point shall provide a Try Another Interface Outcome
                with the following Outcome parameter values and shall continue
                with Outcome Processing, section 3.5.

            Try Another Interface:
                - Start: N/A
                - Online Response Data: N/A
                - CVM: N/A
                - UI Request on Outcome Present: Yes
                    o Message Identifier: '18' (“Please Insert or Swipe Card”)
                    o Status: Processing Error
                - UI Request on Restart Present: No
                - Data Record Present: No
                - Discretionary Data Present: No
                - Alternate Interface Preference: N/A
                - Receipt: N/A
                - Field Off Request: N/A
                - Removal Timeout: Zero
        OTHERWISE (at least one Combination is allowed) Entry Point shall
                retain the Entry Point Pre-Processing Indicators for each allowed
                Combination.
    */
    resetOutcome(&pEp->outcome);
    // TODO UI Request on Outcome Present
    return SUCCESS;
}
//----------------------------------------------------------------------------------------------------
