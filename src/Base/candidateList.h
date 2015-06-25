#ifndef _CANDIDATE_LIST_H_
#define _CANDIDATE_LIST_H_
#include "select.h"

#define CANDLIST_84_BIT         0
#define CANDLIST_DFNAME_BIT     CANDLIST_84_BIT

#define CANDLIST_4F_BIT         1
#define CANDLIST_APPID_BIT      CANDLIST_4F_BIT

#define CANDLIST_50_BIT         2
#define CANDLIST_APPLABEL_BIT   CANDLIST_50_BIT

#define CANDLIST_87_BIT         3
#define CANDLIST_API_BIT        CANDLIST_87_BIT

#define CANDLIST_9F2A_BIT       4
#define CANDLIST_KERNELID_BIT   CANDLIST_9F2A_BIT

typedef struct {
    unsigned char bitmap;
    unsigned char _84[1];    // DFName
    unsigned char _4F[1 + 16];    // Application Id
    unsigned char _50[1 + 16];    // Application label
    unsigned char _87[1 + 1];    // Application Priority Indicator
    unsigned char _9F2A[1 + 1];  // Kernel Id
} CandidateListItem, *CandidateListItemPtr;

#define IS_EXIST_CANDLIST_DFNAME(l)         CHECK_BIT((l), CANDLIST_DFNAME_BIT  )
#define IS_EXIST_CANDLIST_APPID(l)          CHECK_BIT((l), CANDLIST_APPID_BIT   )
#define IS_EXIST_CANDLIST_APPLABEL(l)       CHECK_BIT((l), CANDLIST_APPLABEL_BIT)
#define IS_EXIST_CANDLIST_API(l)            CHECK_BIT((l), CANDLIST_API_BIT     )
#define IS_EXIST_CANDLIST_KERNELID(l)       CHECK_BIT((l), CANDLIST_KERNELID_BIT)

int clearCandidateList(CandidateListItemPtr pList, int size);
int addCandidateList(CandidateListItemPtr   pList, 
                     int*                   pSize,
                     int                    maxSize, 
                     CandidateListItemPtr   item);
int fciToCandidateItem(FciIssDataPtr pFciData, CandidateListItemPtr pItem);

#endif// _CANDIDATE_LIST_H_
