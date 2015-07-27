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
#define MAX_4F_LEN          (1+16)   // First byte keeps length
#define MAX_50_LEN          (1+16)
#define MAX_87_LEN          (1+ 1)
#define MAX_9F2A_LEN        (1+ 8)
#define MAX_9F29_LEN        (1+20)  // TODO unknown max
#define MAX_84_LEN          (1+16)
#define MAX_ISSDATA         10

typedef struct {
    unsigned char   _4F     [MAX_4F_LEN  ];     // ADF Name
    unsigned char   _50     [MAX_50_LEN  ];     // Application Label
    unsigned char   _87     [MAX_87_LEN  ];     // Application priority indicator
    unsigned char   _9F2A   [MAX_9F2A_LEN];     // Kernel identifier
    unsigned char   _9F29   [MAX_9F29_LEN];     // Extended selection
} DirectoryEntry, *DirectoryEntryPtr;

typedef struct {
    unsigned char    _84     [MAX_84_LEN];
    DirectoryEntry  _directoryEntry[MAX_ISSDATA];
    int             _directoryEntryCount;
} Fci, *FciPtr;

int _clearFci(FciPtr r);
int _setDirectoryEntry(FciPtr r, int tag, const unsigned char *value, int size);
int foo(FciPtr r, int tag, const unsigned char *value, int size);
int _set84(FciPtr r, const unsigned char* val, int size);
int _incDirectoryEntryCounter(FciPtr r);

int             getAdfNameLen(DirectoryEntryPtr p);
unsigned char*  getAdfName(DirectoryEntryPtr p);

int             getApplicationLabelLen(DirectoryEntryPtr p);
unsigned char*  getApplicationLabel(DirectoryEntryPtr p);

int             getAPILen(DirectoryEntryPtr p);
int             getAPI(DirectoryEntryPtr p);

int             getKernelIdLen(DirectoryEntryPtr p);
int             getKernelId(DirectoryEntryPtr p);
int             isKernelIdExist(DirectoryEntryPtr p);

int             isAdfNameExist(DirectoryEntryPtr p);
int             isAdfNameValid(DirectoryEntryPtr p);

int             getShortKernelId(DirectoryEntryPtr p);


typedef enum {
    InternationalKernel,
    DomesticKernelEmvCoFormat,
    DomesticKernelPropFormat,
    RfuKernel,
} TypeOfKernels;
#define INTERNATIONALKERNEL_MASK    0x00

TypeOfKernels getKernelType(DirectoryEntryPtr p);

#endif  // MODULAR_SRC_EMV_FCI_H_
