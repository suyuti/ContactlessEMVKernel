#include "candidateList.h"
#include "./err.h"

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

    //memcpy(pItem->_84,      pFciData->_84,      16); // TODO
    memcpy(pItem->_50,      pFciData->_50,      16); // TODO
    memcpy(pItem->_87,      pFciData->_87,      16); // TODO
    memcpy(pItem->_9F2A,    pFciData->_9F2A,    16); // TODO

    return SUCCESS;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
