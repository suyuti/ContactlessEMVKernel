#ifndef _TEST_UTILS_H_
#define _TEST_UTILS_H_

#include "../BaseTest.h"

extern "C" {
    #include "Base/utils.h"
    #include "Base/err.h"
}

class Test_Utils : public BaseTest {
public:
};

//-----------------------------------------------------------------------

TEST_F(Test_Utils, startsWith) {
    int actual = startsWith("1234", "1234");
    EXPECT_EQ(TRUE, actual);

    actual = startsWith("1234", "123");
    EXPECT_EQ(TRUE, actual);

    actual = startsWith("1234", "1");
    EXPECT_EQ(TRUE, actual);

    actual = startsWith("12", "123");
    EXPECT_EQ(FALSE, actual);

    actual = startsWith("1234", "ABC");
    EXPECT_EQ(FALSE, actual);

    actual = startsWith("1234", "");
    //EXPECT_EQ(FALSE, actual);

    actual = startsWith("", "123");
    EXPECT_EQ(FALSE, actual);

    actual = startsWith("", "");
    EXPECT_EQ(TRUE, actual);          // TODO is expected value 0 or -1?

}

TEST_F(Test_Utils, startsWithBin) {
    unsigned char buffer1[] = {0x01, 0x02, 0x03, 0x04, 0x05 };
    unsigned char buffer2[] = {0x01, 0x02, 0x03 };
    unsigned char buffer3[] = {0x0A, 0x0B };

    int actual = startsWithBin( buffer1, sizeof(buffer1),
                                buffer2, sizeof(buffer2));
    EXPECT_EQ(TRUE, actual);

    actual = startsWithBin( buffer2, sizeof(buffer2),
                            buffer1, sizeof(buffer1));
    EXPECT_EQ(FALSE, actual);

    actual = startsWithBin( buffer1, sizeof(buffer1),
                            buffer3, sizeof(buffer3));
    EXPECT_EQ(FALSE, actual);

}

#endif //_TEST_UTILS_H_