#ifndef _TEST_2EA_002_02_H_
#define _TEST_2EA_002_02_H_

#include "../BaseTest.h"

class Test_2EA_002_02 : public BaseTest {
public:
    Test_2EA_002_02() : BaseTest("2EA_002_02") {};
    virtual ~Test_2EA_002_02() {};
};

TEST_F(Test_2EA_002_02, case01) {
    cout << getName() << " case 01" << endl;
}


#endif// _TEST_2EA_002_02_H_
