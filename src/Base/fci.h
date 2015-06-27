#ifndef _FCI_H_
#define _FCI_H_

/*----------------------------------------------------------------------
    Book B p.21
    Table 3-2
    SELECT Response Message Data Field (FCI) of the PPSE
*/
#define MAX_4F_LEN          (1+16)  // First byte keeps length
#define MAX_50_LEN          (1+16)
#define MAX_87_LEN          (1+ 1)
#define MAX_9F2A_LEN        (1+ 1)
#define MAX_84_LEN          (1+16)
#define MAX_ISSDATA         10

typedef struct {
    unsigned char   _4F     [MAX_4F_LEN  ];   // ADF Name
    unsigned char   _50     [MAX_50_LEN  ];   // Application Label
    unsigned char   _87     [MAX_87_LEN  ];   // Application priority indicator
    unsigned char   _9F2A   [MAX_9F2A_LEN];   // Kernel identifier
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

int getAdfNameLen(FciPtr p, int index);
unsigned char* getAdfName(FciPtr p, int index);

int getApplicationLabelLen(FciPtr p, int index);
unsigned char* getApplicationLabel(FciPtr p, int index);

int getAPILen(FciPtr p, int index);
int getAPI(FciPtr p, int index);

int getKernelIdLen(FciPtr p, int index);
int getKernelId(FciPtr p, int index);

#endif// _FCI_H_
