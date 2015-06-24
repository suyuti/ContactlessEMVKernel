#include "epProtocolActivation.h"
#include "../Base/err.h"

//-----------------------------------------------------------------------------

int epProtocolActivation()
{
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_2_1_1() 
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
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_2_1_2()
{
    /*
        Book B v2.5 p.18
        3.2.1.2

        IF      the Restart flag is 1,
        AND     the value of the retained5 UI Request on Restart Present
                parameter is 'Yes',
        THEN    Entry Point shall send the retained User Interface Request.
        OTHERWISE (the Restart flag is 0 or the value of the retained
                UI Request on Restart Present parameter is 'No'), Entry Point shall
                send a User Interface Request with the following parameters:
                - Message Identifier: '15' (“Present Card”)
                - Status: Ready to Read
    */
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_2_1_3()
{
    /*
        Book B v2.5 p.18
        3.2.1.3

        The field shall be powered up and polling performed as defined in
        the Main Loop of Book D.    
    */
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_2_1_4()
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
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_2_1_5()
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
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int _3_2_1_6()
{
    /*
        Book B v2.5 p.18
        3.2.1.6

        As described in Book D requirement 6.4.1.12, Entry Point shall not
        use a higher layer command in the Higher layer - INF field of the
        ATTRIB command.
    */
    return SUCCESS;
}

//-----------------------------------------------------------------------------
