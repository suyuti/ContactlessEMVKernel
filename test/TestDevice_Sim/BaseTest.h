#ifndef _BASE_TEST_H_
#define _BASE_TEST_H_

#include <string>

using namespace std; 

typedef pair<string, string>        Command_Response;
typedef vector<Command_Response>    Command_Response_Pairs;

class BaseTest : public ::testing::Test {
private:
    string                  name:
    Command_Response_Pairs  cr_pairs;
protected:
    BaseTest() {};
    BaseTest(string& name) {
        setName(name);
    };
    virtual ~BaseTest() {};

    virtual void SetUp() {
        clearCommandResponse();
    }
    virtual void TearDown() {

    }

    void addCommandResponse(string cmd, string resp);
    void clearCommandResponse();

public:
    void setName(string& name) { this->name = name;};
    string getName() { return this->name;};

    void executeTest();

};

#endif// _BASE_TEST_H_
