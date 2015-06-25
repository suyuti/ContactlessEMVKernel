#ifndef _TEST_CANDIDATELIST_H_
#define _TEST_CANDIDATELIST_H_

#include "../BaseTest.h"

extern "C" {
    #include "Base/candidateList.h"
    #include "Base/err.h"
}

class Test_CandidateList : public BaseTest {
public:
};

//-----------------------------------------------------------------------------

TEST_F(Test_CandidateList, clearCandidateList_Negative) {
    int actual = clearCandidateList(NULL, 0);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(Test_CandidateList, clearCandidateList) {
    CandidateListItem items[10];
    items[0]._84[0] = 0xFF;
    EXPECT_EQ(0xFF, items[0]._84[0]);

    int actual = clearCandidateList(items, 10);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(0x00, items[0]._84[0]);
}

//-----------------------------------------------------------------------------

TEST_F(Test_CandidateList, addCandidateList_Negative) {
    int count = 0;
    CandidateListItem items[10];
    CandidateListItem item;
    int actual = addCandidateList(NULL, &count, 10, &item);
    EXPECT_EQ(NULL_PARAMETER, actual);
    
    actual = addCandidateList(items, &count, 10, NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);

    actual = addCandidateList(items, NULL, 10, &item);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(Test_CandidateList, addCandidateList) {
    int count = 0;
    CandidateListItem items[10];
    memset(items, 0x00, sizeof(items));
    CandidateListItem item;
    item._84[0] = 0x84;

    int actual = addCandidateList(items, &count, 10, &item);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(1, count);
    EXPECT_EQ(0x84, items[0]._84[0]);

    item._84[0] = 0xFF;
    actual = addCandidateList(items, &count, 10, &item);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_EQ(2, count);
    EXPECT_EQ(0x84, items[0]._84[0]);
    EXPECT_EQ(0xFF, items[1]._84[0]);
    EXPECT_EQ(0x00, items[2]._84[0]);
}

//-----------------------------------------------------------------------------

TEST_F(Test_CandidateList, fciToCandidateItem_Negative) {
    FciIssData          fci;
    CandidateListItem   item;

    int actual = fciToCandidateItem(NULL, NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);

    actual = fciToCandidateItem(&fci, NULL);
    EXPECT_EQ(NULL_PARAMETER, actual);
    
    actual = fciToCandidateItem(NULL, &item);
    EXPECT_EQ(NULL_PARAMETER, actual);
}

//-----------------------------------------------------------------------------

TEST_F(Test_CandidateList, fciToCandidateItem) {
/*    FciIssData          fci;
    CandidateListItem   item;

    unsigned char _4FData[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
                                0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B,
                                0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11,
                                0x12};
    unsigned char _50Data[] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
                                0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B,
                                0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21,
                                0x22, 0x23};
    unsigned char _87Data[] = { 0x00, 0x01};
    unsigned char _9F2AData[] = { 0x00, 0x01};

    _setFciIssData(&fci, 0x4F,   _4FData, sizeof(_4FData));
    _setFciIssData(&fci, 0x50,   _4FData, sizeof(_50Data));
    _setFciIssData(&fci, 0x87,   _4FData, sizeof(_87Data));
    _setFciIssData(&fci, 0x9F2A, _4FData, sizeof(_9F2AData));

    int actual = fciToCandidateItem(&fci, &item);
    EXPECT_EQ(SUCCESS, actual);
    EXPECT_TRUE(memcmp(item._4F, _4FData, sizeof(_4FData)) == 0);
    */
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif// _TEST_CANDIDATELIST_H_
