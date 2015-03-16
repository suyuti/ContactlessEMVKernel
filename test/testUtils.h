#ifndef _TEST__UTILS_H_
#define _TEST__UTILS_H_

#include <string>

using namespace std;

namespace EmvTest {
class TestUtils {
public:

static inline int str2bcd(string str, unsigned char* pOut) {
    if ((str.size() % 2) != 0) return 0;
    int j = 0;
    char c;
    for(int i = 0; i<str.size();++i) {
        c = str[i];
        if (c>='0' && c<='9') {
            c -= '0';
        }
        else if (c>='a' && c<='f') {
            c -= 'a';
            c+=0x0A;
        }
        else if (c>='A' && c<='F') {
            c -= 'A';
            c+=0x0A;
        }
        else {
            return 0;
        }

        if ((i%2) == 0) {
            pOut[j] = c << 4;
        }
        else {
            pOut[j] |= c & 0x0f;
            j++;
        }
    }
    return j;
}

static inline string bcd2str(unsigned char* pIn, int size) {
    if (size <= 0 || pIn == NULL) return "";
    char c, t;
    string s = "";
    for (int i = 0;i < size; ++i) {
        c = pIn[i] >> 4;
        if (c >= 0x00 && c <= 0x09) {
            c += '0';
        }
        else if (c>=0x0A && c <= 0x0F) {
            c += 'A' - 0x0a;
        }
        s += c;

        c = pIn[i] & 0x0F;
        if (c >= 0x00 && c <= 0x09) {
            c += '0';
        }
        else if (c>=0x0A && c <= 0x0F) {
            c += 'A' - 0x0A;
        }
        s += c;
    }
    return s;
}

static inline void log(const unsigned char* pData, int size) {

    for(int i = 0; i < size; ++i) {
        printf("%02X ", pData[i]);
        if ((i!=0) && ((i%16) == 0)) {
            printf("\n");
        }
    }
    printf("\n");
}
};
}

#endif //_TEST_UTILS_H_