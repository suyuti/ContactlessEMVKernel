#include "candidateList.h"
#include "./err.h"
#include "./debug.h"

int clearCandidateList(CandidateListItemPtr pList, int size)
{
    if (!pList) return NULL_PARAMETER;

    memset(pList, 0x00, size * sizeof(CandidateListItem));
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int addCandidateList(CandidateListItemPtr   pList, 
                     int*                   pCount,
                     int                    maxSize, 
                     CandidateListItemPtr   pItem)
{
    if (!pList || !pItem || !pCount) return NULL_PARAMETER;
    if (*pCount >= maxSize) return INDEX_OUT_OF_RANGE;
    memcpy(&(pList[*pCount]), pItem, sizeof(CandidateListItem));
    (*pCount)++;
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int fciToCandidateItem(FciIssDataPtr pFciData, CandidateListItemPtr pItem)
{
    if (!pFciData || !pItem) return NULL_PARAMETER;

    //memcpy(pItem->_84,      pFciData->_84,      16);      // TODO
    memcpy(pItem->_4F,   pFciData->_4F,      MAX_4F_LEN);   // TODO
    memcpy(pItem->_50,   pFciData->_50,      MAX_50_LEN);   // TODO
    memcpy(pItem->_87,   pFciData->_87,      MAX_87_LEN);   // TODO
    memcpy(pItem->_9F2A, pFciData->_9F2A,    MAX_9F2A_LEN); // TODO
    memcpy(pItem->_9F29, pFciData->_9F29,    MAX_9F29_LEN); // TODO
    
    return SUCCESS;
}

//-----------------------------------------------------------------------------

int getApplicationPriority(CandidateListItemPtr p)
{
    if (!p) return NULL_PARAMETER;
    return (int)p->_87[1];
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
