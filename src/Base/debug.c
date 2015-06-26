#include "debug.h"
#include "candidateList.h"

void printCandidateListItem(CandidateListItemPtr item)
{
    int i = 0;
    fprintf(stderr, "CandidateListItem:\n");
    fprintf(stderr, "_84  : ");
    for (i = 0; i < 1; ++i) {
        fprintf(stderr, "%02X ", item->_84[i]);
    }
    fprintf(stderr, "\n");

    fprintf(stderr, "_4F  : ");
    for (i = 0; i < 17; ++i) {
        fprintf(stderr, "%02X ", item->_4F[i]);
    }
    fprintf(stderr, "\n");

    fprintf(stderr, "_50  : ");
    for (i = 0; i < 17; ++i) {
        fprintf(stderr, "%02X ", item->_50[i]);
    }
    fprintf(stderr, "\n");

    fprintf(stderr, "_87  : ");
    for (i = 0; i < 2; ++i) {
        fprintf(stderr, "%02X ", item->_87[i]);
    }
    fprintf(stderr, "\n");
    
    fprintf(stderr, "_9F2A: ");
    for (i = 0; i < 1; ++i) {
        fprintf(stderr, "%02X ", item->_9F2A[i]);
    }
    fprintf(stderr, "\n");
    fprintf(stderr, "\n");
}

void printFci(FciPtr pFci)
{
    int i = 0;
    fprintf(stderr, "Fci : \n");
    fprintf(stderr, "_84  : ");
    for (i = 0; i < 1; ++i) {
        fprintf(stderr, "%02X ", pFci->_84[i]);
    }
    fprintf(stderr, "\n");
    fprintf(stderr, "DataCount: %d\n", pFci->_fciIssDataCount);

    for (i = 0; i < pFci->_fciIssDataCount; ++i) {
        printFciIssData(&(pFci->_fciIssData[i]));
    }
}

void printFciIssData(FciIssDataPtr item)
{
    int i = 0;
    fprintf(stderr, "FciIssData:\n");
    fprintf(stderr, "_4F  : ");
    for (i = 0; i < 17; ++i) {
        fprintf(stderr, "%02X ", item->_4F[i]);
    }
    fprintf(stderr, "\n");

    fprintf(stderr, "_50  : ");
    for (i = 0; i < 17; ++i) {
        fprintf(stderr, "%02X ", item->_50[i]);
    }
    fprintf(stderr, "\n");

    fprintf(stderr, "_87  : ");
    for (i = 0; i < 2; ++i) {
        fprintf(stderr, "%02X ", item->_87[i]);
    }
    fprintf(stderr, "\n");
    
    fprintf(stderr, "_9F2A: ");
    for (i = 0; i < 1; ++i) {
        fprintf(stderr, "%02X ", item->_9F2A[i]);
    }
    fprintf(stderr, "\n");
    fprintf(stderr, "\n");
}
