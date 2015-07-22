/*
    Copyright 2015
*/

#ifndef MODULAR_SRC_COMMON_HAL_H_
#define MODULAR_SRC_COMMON_HAL_H_


//- SmartCard IO
typedef int     (*_card_open)(void);
typedef int     (*_card_reset)(void);
typedef int     (*_card_close)(void);
typedef int     (*_card_transmit)(  const unsigned char*  pIn,
                                    int                   inSize,
                                    unsigned char*        pOut,
                                    unsigned long*        pOutSize);

//- File IO
typedef int     (*_fileOpen)(const char* fileName,
                             const char* mode);
typedef int     (*_fileClose)(int file);
typedef int     (*_getFileSize)(int file);
typedef int     (*_fileRead)(int    file,
                             char*  buffer,
                             int    size);

//- Memory management
typedef void*   (*_allocate)(int size);
typedef void    (*_release)(void* p);

//- Generating unpredictable number
typedef int (*genUnPredNum)(unsigned char* pOut,
                            unsigned long* pOutSize);

#define GENERATE_UNPREDICT_NUMBER(p, n, l)  (p)->_genUnPredNum((n), (l))

typedef struct {
    _card_open      card_open;
    _card_reset     card_reset;
    _card_close     card_close;
    _card_transmit  card_transmit;
    _fileOpen       fileOpen;
    _fileClose      fileClose;
    _fileRead       fileRead;
    _getFileSize    getFileSize;
    _allocate       allocate;
    _release        release;
    genUnPredNum    _genUnPredNum;
} HalInterfaces, *HalInterfacesPtr;




typedef enum {
    RandomNumberGenerator,
    CardReaderOpen,
    CardReaderClose,
} HalInterfaceTypes;

#define SET_DELEGATE_CARD_OPEN(halPtr, foo)         (halPtr)->card_open      = foo
#define SET_DELEGATE_CARD_RESET(halPtr, foo)        (halPtr)->card_reset     = foo
#define SET_DELEGATE_CARD_CLOSE(halPtr, foo)        (halPtr)->card_close     = foo
#define SET_DELEGATE_CARD_TRANSMIT(halPtr, foo)     (halPtr)->card_transmit  = foo

#define CARD_RESET(halPtr)                          (halPtr)->card_reset()
#define CARD_OPEN(halPtr)                           (halPtr)->card_open()
#define CARD_CLOSE(halPtr)                          (halPtr)->card_close()
#define CARD_TRANSMIT(halPtr, i, is, o, os)         (halPtr)->card_transmit((i), (is), (o), (os))

#define SET_DELEGATE_FILE_OPEN(halPtr, foo)         (halPtr)->fileOpen      = foo
#define SET_DELEGATE_FILE_CLOSE(halPtr, foo)        (halPtr)->fileClose     = foo
#define SET_DELEGATE_FILE_READ(halPtr, foo)         (halPtr)->fileRead      = foo
#define SET_DELEGATE_GET_FILE_SIZE(halPtr, foo)     (halPtr)->getFileSize   = foo

//#define FILE_OPEN_R(halPtr, name)                   FILE_OPEN((halPtr), (name), "r")  // ReadOnly mode
//#define FILE_OPEN(halPtr, name, mode)               (halPtr)->fileOpen((name), (mode))
//#define FILE_CLOSE(halPtr, file)                    (halPtr)->fileClose((file))
//#define GET_FILE_SIZE(halPtr, file)                 (halPtr)->getFileSize((file))
//#define FILE_READ(halPtr, file, o, s)               (halPtr)->fileRead((file), (o), (s))


#define SET_DELEGATE_ALLOCATE(halPtr, foo)          (halPtr)->allocate  = foo
#define SET_DELEGATE_RELEASE(halPtr, foo)           (halPtr)->release   = foo
#define ALLOCATE(halPtr, size)                      (halPtr)->allocate((size))
#define RELEASE(halPtr, obj)                        (halPtr)->release((obj))

#define SET_DELEGATE_GENUNPREDNUM(halPtr, foo)      (halPtr)->_genUnPredNum   = foo
#define GENERATE_UNPRED_NUM(halPtr)                 (halPtr)->_genUnPredNum()


int checkHalInterfaces(void);

int card_transmit(const unsigned char* pIn, int inSize, unsigned char* pOut, unsigned long* pOutSize);
int fileOpen(const char* fileName, const char* mode);
int fileClose(int file);
int getFileSize(int file);
int fileRead(int file, char* buffer, int size);
void* allocate(int size);
void release(void* p);




int setCardOpen(_card_open f);
int setCardReset(_card_reset f);
int setCardClose(_card_close f);
int setCardTransmit(_card_transmit f);
int setFileOpen(_fileOpen f);
int setFileClose(_fileClose f);
int setFileRead(_fileRead f);
int setGetFileSize(_getFileSize f);
int setAllocate(_allocate f);
int setRelease(_release f);
int setGenUnPredNum(genUnPredNum f);


#endif  // MODULAR_SRC_COMMON_HAL_H_
