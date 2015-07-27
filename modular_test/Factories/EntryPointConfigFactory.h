
#ifndef _MODULAR_TEST_ENTRYPOINT_CONFIG_FACTORY_H_
#define _MODULAR_TEST_ENTRYPOINT_CONFIG_FACTORY_H_

#include <string>
#include <string.h> // memset
using namespace std;

extern "C" {
#include "EntryPoint/epConfig.h"
}

class EntryPointConfigs {
private:
    class EntryPointConfigProperties {
    private:
        EntryPointConfigProperties() {
            memset(&config, 0x00, sizeof(EpConfig));
        }
        EpConfig        config;

        friend class EntryPointConfigs;
        friend class EntryPointConfigBuilder;
    };
public:

    EntryPointConfigs() {}

    class EntryPointConfigBuilder {
    public:
        EntryPointConfigBuilder() {}
        EntryPointConfigBuilder& WithStatusCheck(unsigned char v);
        EntryPointConfigBuilder& WithZeroAmountAllowed(unsigned char v);
        EntryPointConfigBuilder& WithClessTrnxLimit(int v);
        EntryPointConfigBuilder& WithClessFloorLimit(int v);
        EntryPointConfigBuilder& WithTermFloorLimit(int v);
        EntryPointConfigBuilder& WithCvmRequiredLimit(int v);
        EntryPointConfigBuilder& WithTtq(string v);
        EntryPointConfigBuilder& WithTtq(unsigned char v[4]);
        EntryPointConfigBuilder& WithExtendedSelectionSupport(unsigned char v);
        EntryPointConfigBuilder& WithAid(string aid);
        EntryPointConfigBuilder& WithKernelId(unsigned char kid);
        EntryPointConfigBuilder& WithStatusCheckTequested(bool v);            // indicator
        EntryPointConfigBuilder& WithClessAppNotAllowed(bool v);              // indicator
        EntryPointConfigBuilder& WithZeroAmount(bool v);                      // indicator
        EntryPointConfigBuilder& WithReaderCVMReqLimitExceeded(bool v);       // indicator
        EntryPointConfigBuilder& WithReaderClessFloorLimitExceeded(bool v);   // indicator
        EntryPointConfigBuilder& WithCopyTtq(bool v);                         // indicator

        EntryPointConfigs Build();

    private:
        EntryPointConfigProperties fProperties;
    };
public:
    string toString();
    void save(string name);
    void copy(EpConfigPtr p);


private:
    EntryPointConfigs(const EntryPointConfigProperties& properties) : fProperties(properties) {}

protected:

    EntryPointConfigProperties fProperties;
};

#endif  // _MODULAR_TEST_ENTRYPOINT_CONFIG_FACTORY_H_
