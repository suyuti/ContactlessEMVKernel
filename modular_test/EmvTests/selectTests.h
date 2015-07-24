/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#ifndef MODULAR_TEST_EMVTESTS_SELECTTESTS_H_
#define MODULAR_TEST_EMVTESTS_SELECTTESTS_H_
#include <string>
#include "../BaseTest.h"
#include "../testUtils.h"

extern "C" {
    #include "Emv/select.h"
    #include "Common/err.h"
    #include "Common/general.h"
}

class Test_Select : public BaseTest {
 public:
};

//-----------------------------------------------------------------------

TEST_F(Test_Select, _buildSelect)
{
    unsigned char aid[] = {0xA0, 0x01, 0x02, 0x03, 0x04};
    unsigned char buffer[255];
    unsigned long size;
    unsigned char expectedBuffer[] = {0x00, 0xA4, 0x04, 0x00,
                                      0x05,
                                      0xA0, 0x01, 0x02, 0x03, 0x04};

    int actual = _buildSelect((const unsigned char*)aid,
                              sizeof(aid),
                              buffer,
                              &size);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(10, size);
    EXPECT_EQ(0, memcmp(buffer, expectedBuffer, sizeof(expectedBuffer)));
}

//-----------------------------------------------------------------------

TEST_F(Test_Select, _buildSelect_Negative)
{
    char aid[] = {0xA0, 0x01, 0x02, 0x03, 0x04};
    unsigned char buffer[255];
    unsigned long size;
    unsigned char expectedBuffer[] = {0x00, 0xA4, 0x04, 0x00,
                                      0x05,
                                      0xA0, 0x01, 0x02, 0x03, 0x04};

    int actual = _buildSelect(NULL,
                              sizeof(aid),
                              buffer,
                              &size);
    EXPECT_EQ(NULL_PARAMETER, actual);
    actual = _buildSelect((const unsigned char*)aid,
                              sizeof(aid),
                              NULL,
                              &size);
    EXPECT_EQ(NULL_PARAMETER, actual);
    actual = _buildSelect((const unsigned char*)aid,
                              sizeof(aid),
                              buffer,
                              NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
    actual = _buildSelect((const unsigned char*)aid,
                              0,
                              buffer,
                              &size);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------

TEST_F(Test_Select, _buildSelectPpse_Negative)
{
    unsigned char buffer[256];
    unsigned long size;

    int actual = _buildSelectPpse(NULL, &size);
    EXPECT_EQ(NULL_PARAMETER, actual);

    actual = _buildSelectPpse(buffer, NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------

TEST_F(Test_Select, _buildSelectPpse)
{
    unsigned char buffer[256];
    unsigned long size;
    unsigned char expectedBuffer[] = {
        0x00, 0xA4, 0x04, 0x00,
        0x0E,
        '2', 'P', 'A', 'Y', '.', 'S', 'Y',
        'S', '.', 'D', 'D', 'F', '0', '1',
    };

    int actual = _buildSelectPpse(buffer, &size);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(0, memcmp(buffer, expectedBuffer, sizeof(expectedBuffer)));
    EXPECT_EQ(19, size);
}

//-----------------------------------------------------------------------

TEST_F(Test_Select, _clearFci_Negative)
{
    int actual = _clearFci(NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------

TEST_F(Test_Select, _clearFci)
{
    Fci fci;
    fci._84[0] = 0xFF;

    int actual = _clearFci(&fci);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(0x00, fci._84[0]);
}

//-----------------------------------------------------------------------

TEST_F(Test_Select, _setFciIssData_Negative)
{
    Fci fci;
    unsigned char value[] = {0xAB, 0xCD};
    int actual = _setFciIssData(NULL,
                                0x4F,
                                value,
                                sizeof(value));
    EXPECT_EQ(NULL_PARAMETER, actual);

    fci._fciIssDataCount = 0;
    actual = _setFciIssData(&fci,
                            0x4F,
                            value,
                            sizeof(value));
    EXPECT_EQ(INDEX_OUT_OF_RANGE, actual);

    fci._fciIssDataCount = 1;
    actual = _setFciIssData(&fci,
                            0x4F,
                            NULL,
                            sizeof(value));
    EXPECT_EQ(NULL_PARAMETER, actual);

    actual = _setFciIssData(&fci,
                            0x4F,
                            value,
                            0);
    EXPECT_EQ(NULL_PARAMETER, actual);

    unsigned char invalid4F[] = "12345678901234567890";
    actual = _setFciIssData(&fci,
                            0x4F,
                            invalid4F,
                            sizeof(invalid4F));
    EXPECT_EQ(INCORRECT_DATA, actual);

    unsigned char invalid50[] = "12345678901234567890";
    actual = _setFciIssData(&fci,
                            0x50,
                            invalid50,
                            sizeof(invalid50));
    EXPECT_EQ(INCORRECT_DATA, actual);

    unsigned char invalid87[] = "12345678901234567890";
    actual = _setFciIssData(&fci,
                            0x87,
                            invalid87,
                            sizeof(invalid87));
    EXPECT_EQ(INCORRECT_DATA, actual);

    unsigned char invalid9F2A[] = "12345678901234567890";
    actual = _setFciIssData(&fci,
                            0x9F2A,
                            invalid9F2A,
                            sizeof(invalid9F2A));
    EXPECT_EQ(INCORRECT_DATA, actual);

    unsigned char unknownData[] = "12345678901234567890";
    actual = _setFciIssData(&fci,
                            0xABCD,
                            unknownData,
                            sizeof(unknownData));
    EXPECT_EQ(UNKNOWN_TAG, actual);
}

//-----------------------------------------------------------------------

TEST_F(Test_Select, _setFciIssData)
{
    Fci fci;
    memset(&fci, 0x00, sizeof(Fci));

    unsigned char _4FData[]          = {0x4F, 0x4F};
    unsigned char expected4FData[]   = {0x02, 0x4F, 0x4F};
    unsigned char _50Data[]          = {0x50, 0x50};
    unsigned char expected50Data[]   = {0x02, 0x50, 0x50};
    unsigned char _87Data[]          = {0x87};
    unsigned char expected87Data[]   = {0x01, 0x87};
    unsigned char _9F2AData[]        = {0x9F};
    unsigned char expected9F2AData[] = {0x01, 0x9F};

    _incFciIssDataCounter(&fci);
    int actual = _setFciIssData(&fci,
                                0x4F,
                                _4FData,
                                sizeof(_4FData));
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(0, memcmp(fci._fciIssData[0]._4F, expected4FData, sizeof(expected4FData)));

    actual = _setFciIssData(&fci,
                            0x50,
                            _50Data,
                            sizeof(_50Data));
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(0, memcmp(fci._fciIssData[0]._50,
                       expected50Data,
                       sizeof(expected50Data)));

    actual = _setFciIssData(&fci,
                            0x87,
                            _87Data,
                            sizeof(_87Data));
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(0, memcmp(fci._fciIssData[0]._87,
                       expected87Data,
                       sizeof(expected87Data)));

    actual = _setFciIssData(&fci,
                            0x9F2A,
                            _9F2AData,
                            sizeof(_9F2AData));
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(0, memcmp(fci._fciIssData[0]._9F2A,
                       expected9F2AData,
                       sizeof(expected9F2AData)));
}
//-----------------------------------------------------------------------

TEST_F(Test_Select, _incFciIssDataCounter_Negative)
{
    int actual = _incFciIssDataCounter(NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------

TEST_F(Test_Select, _incFciIssDataCounter)
{
    Fci fci;
    memset(&fci, 0x00, sizeof(Fci));

    int actual = _incFciIssDataCounter(&fci);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(1, fci._fciIssDataCount);

    actual = _incFciIssDataCounter(&fci);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(2, fci._fciIssDataCount);

    actual = _incFciIssDataCounter(&fci);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(3, fci._fciIssDataCount);

    actual = _incFciIssDataCounter(&fci);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(4, fci._fciIssDataCount);

    actual = _incFciIssDataCounter(&fci);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(5, fci._fciIssDataCount);

    actual = _incFciIssDataCounter(&fci);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(6, fci._fciIssDataCount);

    actual = _incFciIssDataCounter(&fci);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(7, fci._fciIssDataCount);

    actual = _incFciIssDataCounter(&fci);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(8, fci._fciIssDataCount);

    actual = _incFciIssDataCounter(&fci);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(9, fci._fciIssDataCount);

    actual = _incFciIssDataCounter(&fci);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(10, fci._fciIssDataCount);

    actual = _incFciIssDataCounter(&fci);
    EXPECT_EQ(INDEX_OUT_OF_RANGE, actual);
}

//-----------------------------------------------------------------------

TEST_F(Test_Select, OnTag_resolvePpse_Negative)
{
    Fci fci;
    unsigned char value[] = {0xAB};
    int actual = OnTag_resolvePpse(0x4F, 16, 0, NULL, &fci);
    EXPECT_EQ(NULL_PARAMETER, actual);
    actual = OnTag_resolvePpse(0x4F, 16, 0, value, NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);

    actual = OnTag_resolvePpse(0x4F, 0, 0, value, &fci);
    EXPECT_EQ(NULL_PARAMETER, actual);

    _incFciIssDataCounter(&fci);
    actual = OnTag_resolvePpse(0xFF, sizeof(value), 0, value, &fci);
    EXPECT_EQ(UNKNOWN_TAG, actual);
}

//-----------------------------------------------------------------------

TEST_F(Test_Select, OnTag_resolvePpse)
{
    Fci fci;
    memset(&fci, 0x00, sizeof(Fci));
    unsigned char value[] = {0x61};

    int actual = OnTag_resolvePpse(0x61, 1, 0, value, &fci);

    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(1, fci._fciIssDataCount);

    unsigned char value84[]         = {0xAB, 0xCD};
    unsigned char expectedValue84[] = {0x01, 0xAB, 0xCD};
    actual = OnTag_resolvePpse(0x84, sizeof(value84), 0, value84, &fci);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(0, memcmp(fci._84, expectedValue84, sizeof(expectedValue84)));
}

//-----------------------------------------------------------------------

TEST_F(Test_Select, _resolveSelectPpse_Negative)
{
    unsigned char deadBabe[] = {0xDE, 0xAD, 0xBA, 0xBE};
    Fci fci;

    int actual = _resolveSelectPpse(NULL, sizeof(deadBabe), &fci);
    EXPECT_EQ(NULL_PARAMETER, actual);
    actual = _resolveSelectPpse(deadBabe, 0, &fci);
    EXPECT_EQ(NULL_PARAMETER, actual);

    actual = _resolveSelectPpse(deadBabe, sizeof(deadBabe), NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------

TEST_F(Test_Select, _resolveSelectPpse)
{
    string ppseResponseStr("6F""2D"
                                "84" "0E" "325041592E5359532E4444463031"
                                "A5" "1B"
                                    "BF0C""18"
                                        "61""16"
                                            "4F""07""A0000000010001"
                                            "50""04""41505031"
                                            "9F2A""01""23"
                                            "87""01""01");
    unsigned char ppseResponse[255];
    int len = EmvTest::TestUtils::str2bcd(ppseResponseStr, ppseResponse);
    Fci fci;
    _clearFci(&fci);

    int actual = _resolveSelectPpse(ppseResponse, len, &fci);
    EXPECT_EQ(SUCCESS, actual);

    unsigned char expected4F[] = {0x07, 0xA0, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01};
    EXPECT_EQ(0, memcmp(fci._fciIssData[0]._4F, expected4F, sizeof(expected4F)));

    unsigned char expected50[] = {0x04, 0x41, 0x50, 0x50, 0x31};
    EXPECT_EQ(0, memcmp(fci._fciIssData[0]._50, expected50, sizeof(expected50)));

    unsigned char expected9F2A[] = {0x01, 0x23};
    EXPECT_EQ(0, memcmp(fci._fciIssData[0]._9F2A, expected9F2A, sizeof(expected9F2A)));

    unsigned char expected87[] = {0x01, 0x01};
    EXPECT_EQ(0, memcmp(fci._fciIssData[0]._87, expected87, sizeof(expected87)));
}

//-----------------------------------------------------------------------

TEST_F(Test_Select, selectPpse_Negative)
{
    int actual = selectPpse(NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------

TEST_F(Test_Select, selectPpse)
{
    string ppseResponseStr("6F""2D"
                                "84" "0E" "325041592E5359532E4444463031"
                                "A5" "1B"
                                    "BF0C""18"
                                        "61""16"
                                            "4F""07""A0000000010001"
                                            "50""04""41505031"
                                            "9F2A""01""23"
                                            "87""01""01"
                                            "9000");
    unsigned char ppseResponse[255];
    int len = EmvTest::TestUtils::str2bcd(ppseResponseStr, ppseResponse);
    EXPECT_CALL(halApi, cardTransmit(isApdu("00A404000E325041592E5359532E4444463031"), Ge(5), _, _))
                        .Times(Exactly(1))
                        .WillOnce(
                            DoAll(
                                SetArrayArgument<2>(ppseResponse, ppseResponse+len),
                                SetArgPointee<3>((unsigned long)len),
                                Return(SUCCESS)));
    Fci fci;
    _clearFci(&fci);

    int actual = selectPpse(&fci);
    EXPECT_EQ(SUCCESS, actual);

    unsigned char expected4F[] = {0x07, 0xA0, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01};
    EXPECT_EQ(0, memcmp(fci._fciIssData[0]._4F, expected4F, sizeof(expected4F)));

    unsigned char expected50[] = {0x04, 0x41, 0x50, 0x50, 0x31};
    EXPECT_EQ(0, memcmp(fci._fciIssData[0]._50, expected50, sizeof(expected50)));

    unsigned char expected9F2A[] = {0x01, 0x23};
    EXPECT_EQ(0, memcmp(fci._fciIssData[0]._9F2A, expected9F2A, sizeof(expected9F2A)));

    unsigned char expected87[] = {0x01, 0x01};
    EXPECT_EQ(0, memcmp(fci._fciIssData[0]._87, expected87, sizeof(expected87)));
}

//-----------------------------------------------------------------------

TEST_F(Test_Select, selectPpse_invalidResponse)
{
    string ppseResponseStr("6A85");
    unsigned char ppseResponse[255];
    int len = EmvTest::TestUtils::str2bcd(ppseResponseStr, ppseResponse);
    EXPECT_CALL(halApi, cardTransmit(isApdu("00A404000E325041592E5359532E4444463031"), Ge(5), _, _))
                        .Times(Exactly(1))
                        .WillOnce(
                            DoAll(
                                SetArrayArgument<2>(ppseResponse, ppseResponse+len),
                                SetArgPointee<3>((unsigned long)len),
                                Return(SUCCESS)));
    Fci fci;
    _clearFci(&fci);

    int actual = selectPpse(&fci);
    EXPECT_EQ(SW_NOT_SUCCESS, actual);
    EXPECT_EQ(MAKEWORD(0x6A, 0x85), getLastSw());
}

//-----------------------------------------------------------------------


#endif  // MODULAR_TEST_EMVTESTS_SELECTTESTS_H_
