#ifndef _TEST_CANDIDATELIST_H_
#define _TEST_CANDIDATELIST_H_

#include "../BaseTest.h"

extern "C" {
    #include "Base/candidateList.h"
    #include "Base/err.h"
    #include "Base/debug.h"
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
    Fci          fci;
    CandidateListItem   item;
    memset(&item, 0x00, sizeof(CandidateListItem));


    unsigned char _4FData[] = "ABCDEFGHIJKLMNO";
    unsigned char _50Data[] = { 0x10, 0x11, 0x12, 0x13, 0x14, 
                                0x16, 0x17, 0x18, 0x19, 0x1A, 
                                0x1C, 0x1D, 0x1E, 0x1F, 0x20, 
                                0x22};
    unsigned char _87Data[] = { 0x01};
    unsigned char _9F2AData[] = { 0x01};

    _clearFci(&fci);
    _incFciIssDataCounter(&fci);

    int err = _setFciIssData(&fci, 0x4F,   _4FData, sizeof(_4FData));
    EXPECT_EQ(SUCCESS, err);
    err = _setFciIssData(&fci, 0x50,   _50Data, sizeof(_50Data));
    EXPECT_EQ(SUCCESS, err);
    err = _setFciIssData(&fci, 0x87,   _87Data, sizeof(_87Data));
    EXPECT_EQ(SUCCESS, err);
    err = _setFciIssData(&fci, 0x9F2A, _9F2AData, sizeof(_9F2AData));
    EXPECT_EQ(SUCCESS, err);

    //printFci(&fci);
    //printCandidateListItem(&item);

    int actual = fciToCandidateItem(&(fci._fciIssData[0]), &item);

    //printFci(&fci);
    //printCandidateListItem(&item);
    

    EXPECT_EQ(SUCCESS, actual);
    //debugBin(_4FData, sizeof(_4FData), "_4FData");
    //debugBin(item._4F, 17, "Item");
    EXPECT_TRUE(memcmp(item._4F+1, _4FData, sizeof(_4FData)) == 0);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

#endif// _TEST_CANDIDATELIST_H_
