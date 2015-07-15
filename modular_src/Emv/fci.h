/*
 * Copyright 2015 Suyuti  [legal/copyright]
 *
 * */

#ifndef MODULAR_SRC_EMV_FCI_H_
#define MODULAR_SRC_EMV_FCI_H_

/*----------------------------------------------------------------------
    Book B p.21
    Table 3-2
    SELECT Response Message Data Field (FCI) of the PPSE
*/
#define MAX_4F_LEN          (1+16)  // First byte keeps length
#define MAX_50_LEN          (1+16)
#define MAX_87_LEN          (1+ 1)
#define MAX_9F2A_LEN        (1+ 2)
#define MAX_9F29_LEN        (1+20) // TODO unknown max
#define MAX_84_LEN          (1+16)
#define MAX_ISSDATA         10

typedef struct {
    unsigned char   _4F     [MAX_4F_LEN  ];     // ADF Name
    unsigned char   _50     [MAX_50_LEN  ];     // Application Label
    unsigned char   _87     [MAX_87_LEN  ];     // Application priority indicator
    unsigned char   _9F2A   [MAX_9F2A_LEN];     // Kernel identifier
    unsigned char   _9F29   [MAX_9F29_LEN];     // Extended selection
} FciIssData, *FciIssDataPtr;

typedef struct {
    unsigned char   _84     [MAX_84_LEN];
    FciIssData      _fciIssData[MAX_ISSDATA];
    int             _fciIssDataCount;
} Fci, *FciPtr;

int _clearFci(FciPtr r);
int _setFciIssData(FciPtr r, int tag, const unsigned char* value, int size);
int _set84(FciPtr r, const unsigned char* val, int size);
int _incFciIssDataCounter(FciPtr r);

int             getAdfNameLen(FciIssDataPtr p);
unsigned char*  getAdfName(FciIssDataPtr p);

int             getApplicationLabelLen(FciIssDataPtr p);
unsigned char*  getApplicationLabel(FciIssDataPtr p);

int             getAPILen(FciIssDataPtr p);
int             getAPI(FciIssDataPtr p);

int             getKernelIdLen(FciIssDataPtr p);
int             getKernelId(FciIssDataPtr p);
int             isKernelIdExist(FciIssDataPtr p);

int             isAdfNameExist(FciIssDataPtr p);
int             isAdfNameValid(FciIssDataPtr p);

int             getShortKernelId(FciIssDataPtr p);


        typedef enum {
    InternationalKernel,
    DomesticKernelEmvCoFormat,
    DomesticKernelPropFormat,
    RfuKernel,
} TypeOfKernels;
#define INTERNATIONALKERNEL_MASK    0x00

TypeOfKernels getKernelType(FciIssDataPtr p);

#endif// MODULAR_SRC_EMV_FCI_H_
