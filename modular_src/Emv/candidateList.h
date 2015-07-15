/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#ifndef MODULAR_SRC_EMV_CANDIDATELIST_H_
#define MODULAR_SRC_EMV_CANDIDATELIST_H_
#include "./select.h"
#include "./fci.h"

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

#define CANDLIST_9F29_BIT                   5
#define CANDLIST_EXTENDEDSELECTION_BIT      CANDLIST_9F29_BIT


typedef struct {
    unsigned char bitmap;
    unsigned char _84[MAX_84_LEN];          // DFName
    unsigned char _4F[MAX_4F_LEN];          // Application Id
    unsigned char _50[MAX_50_LEN];          // Application label
    unsigned char _87[MAX_87_LEN];          // Application Priority Indicator
    unsigned char _9F2A[MAX_9F2A_LEN];      // Kernel Id
    unsigned char _9F29[MAX_9F29_LEN];      // Extended Selection
} CandidateListItem, *CandidateListItemPtr;

#define IS_EXIST_CANDLIST_DFNAME(l)             CHECK_BIT((l), CANDLIST_DFNAME_BIT              )
#define IS_EXIST_CANDLIST_APPID(l)              CHECK_BIT((l), CANDLIST_APPID_BIT               )
#define IS_EXIST_CANDLIST_APPLABEL(l)           CHECK_BIT((l), CANDLIST_APPLABEL_BIT            )
#define IS_EXIST_CANDLIST_API(l)                CHECK_BIT((l), CANDLIST_API_BIT                 )
#define IS_EXIST_CANDLIST_KERNELID(l)           CHECK_BIT((l), CANDLIST_KERNELID_BIT            )
#define IS_EXIST_CANDLIST_EXTENTED_SELECTION(l) CHECK_BIT((l), CANDLIST_EXTENDEDSELECTION_BIT   )

int clearCandidateList(CandidateListItemPtr pList, int size);
int addCandidateList(CandidateListItemPtr   pList,
                     int*                   pSize,
                     int                    maxSize,
                     CandidateListItemPtr   item);
int fciToCandidateItem(FciIssDataPtr pFciData, CandidateListItemPtr pItem);
int getApplicationPriority(CandidateListItemPtr p);
#endif// MODULAR_SRC_EMV_CANDIDATELIST_H_
