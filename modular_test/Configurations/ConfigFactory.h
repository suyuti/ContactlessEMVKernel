
#ifndef _TEST_CONFIG_FACTORY_H_
#define _TEST_CONFIG_FACTORY_H_

#include <string>
#include <string.h> // memset
using namespace std;

extern "C" {
    #include "EntryPoint/epConfig.h"
}

class TerminalConfigs {
private:
    class TerminalConfigProperties {
    private:
        TerminalConfigProperties() {
            memset(&config, 0x00, sizeof(EpConfigData));
        }
        EpConfig        config;

        friend class TerminalConfigs;
        friend class TerminalConfigBuilder;
    };
public:
    typedef enum {
        Config01,
        Config02,
        Config03,
        Config04,
        Config05,
        Config06,
        Config07,
        Config08,
        Config10,
        Config13,
    } Configurations;

    TerminalConfigs() {}

    class TerminalConfigBuilder {
    public:
        TerminalConfigBuilder() {}
        TerminalConfigBuilder& WithStatusCheck(unsigned char v);
        TerminalConfigBuilder& WithZeroAmountAllowed(unsigned char v);
        TerminalConfigBuilder& WithClessTrnxLimit(int v);
        TerminalConfigBuilder& WithClessFloorLimit(int v);
        TerminalConfigBuilder& WithTermFloorLimit(int v);
        TerminalConfigBuilder& WithCvmRequiredLimit(int v);
        TerminalConfigBuilder& WithTtq(string v);
        TerminalConfigBuilder& WithTtq(unsigned char v[4]);
        TerminalConfigBuilder& WithExtendedSelectionSupport(unsigned char v);
        TerminalConfigBuilder& WithAid(string aid);
        TerminalConfigBuilder& WithKernelId(unsigned char kid);
        TerminalConfigBuilder& WithStatusCheckTequested(bool v);            // indicator
        TerminalConfigBuilder& WithClessAppNotAllowed(bool v);              // indicator
        TerminalConfigBuilder& WithZeroAmount(bool v);                      // indicator
        TerminalConfigBuilder& WithReaderCVMReqLimitExceeded(bool v);       // indicator
        TerminalConfigBuilder& WithReaderClessFloorLimitExceeded(bool v);   // indicator
        TerminalConfigBuilder& WithCopyTtq(bool v);                         // indicator

        TerminalConfigs Build();

    private:
        TerminalConfigProperties fProperties;
    };
public:
//    virtual TerminalConfigs generate(string kid, string aid, string trnx = "");
    string toString();
    void save(string name);

private:
    TerminalConfigs(const TerminalConfigProperties& properties) : fProperties(properties) {}

protected:

    TerminalConfigProperties fProperties;
};

#endif// _TEST_CONFIG_FACTORY_H_
