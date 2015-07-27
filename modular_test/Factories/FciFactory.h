
#ifndef _MODULAR_TEST_FCI_FACTORY_H_
#define _MODULAR_TEST_FCI_FACTORY_H_

#include <string>
#include <string.h> // memset
using namespace std;

extern "C" {
#include "Emv/fci.h"
}

class FciFactory {
private:
    class FciProperties {
    private:
        FciProperties() {
            memset(&fci, 0x00, sizeof(Fci));
        }
        Fci             fci;

        friend class FciFactory;
        friend class FciBuilder;
    };
public:

    FciFactory() {}

    class FciBuilder {
    public:
        FciBuilder() {}
        FciBuilder& WithFciData(const FciIssData& d);

        FciFactory Build();

    private:
        FciProperties fProperties;
    };
public:
    string toString();
    void copy(FciPtr p);


private:
    FciFactory(const FciProperties& properties) : fProperties(properties) {}

protected:

    FciProperties fProperties;
};

#endif  // _MODULAR_TEST_FCI_FACTORY_H_
