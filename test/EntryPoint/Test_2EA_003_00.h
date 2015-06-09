#ifndef _TEST_2EA_003_00_H_
#define _TEST_2EA_003_00_H_

#include "../BaseTest.h"

class Test_2EA_003_00 : public BaseTest {
public:
    Test_2EA_003_00() : BaseTest("2EA_003_00") {};
    virtual ~Test_2EA_003_00() {};
};

TEST_F(Test_2EA_003_00, case01) {
    cout << getName() << " case 01" << endl;
}


#endif// _TEST_2EA_003_00_H_
