#ifndef _TEST_CONFIG_FACTORY_H_
#define _TEST_CONFIG_FACTORY_H_
#include <string>
#include <string.h> // memset
using namespace std;
extern "C" {
    #include "../../../src/EntryPoint/epConfig.h"
}
class TerminalConfigs {
private:
    class TerminalConfigProperties {
    private:
        TerminalConfigProperties() {
            memset(&config, 0x00, sizeof(EpConfig));
        }
        EpConfig        config;

        friend class TerminalConfigs;
        friend class TerminalConfigBuilder;
    };
public:
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
        TerminalConfigs Build();

    private:
        TerminalConfigProperties fProperties;
    };
private:
    TerminalConfigs(const TerminalConfigProperties& properties) : fProperties(properties) {}

protected:
    TerminalConfigs generateTerminalConfig01();

    TerminalConfigs generateTerminalConfig02(string kernelId, string aid);

    TerminalConfigs generateTerminalConfig02();
    TerminalConfigs generateTerminalConfig03();
    TerminalConfigs generateTerminalConfig04();
    TerminalConfigs generateTerminalConfig05();
    TerminalConfigs generateTerminalConfig06();
    TerminalConfigs generateTerminalConfig07();
    TerminalConfigs generateTerminalConfig08();
    TerminalConfigs generateTerminalConfig09();
    TerminalConfigs generateTerminalConfig10();
    TerminalConfigs generateTerminalConfig11();
    TerminalConfigs generateTerminalConfig12();
    TerminalConfigs generateTerminalConfig13();

    TerminalConfigProperties fProperties;
};

#endif// _TEST_CONFIG_FACTORY_H_
