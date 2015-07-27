
#ifndef _MODULAR_TEST_FCIDATA_FACTORY_H_
#define _MODULAR_TEST_FCIDATA_FACTORY_H_

#include <string>
#include <string.h> // memset
using namespace std;

extern "C" {
    #include "Emv/fci.h"
}

class FciDataFactory {
private:
    class FciDataProperties {
    private:
        FciDataProperties() {
            memset(&fciData, 0x00, sizeof(FciIssData));
        }
        FciIssData             fciData;

        friend class FciDataFactory;
        friend class FciDataBuilder;
    };
public:

    FciDataFactory() {}

    class FciDataBuilder {
    public:
        FciDataBuilder() {}
        FciDataBuilder& WithADFName(string adfName);
        FciDataBuilder& WithApplicationLabel(string label);
        FciDataBuilder& WithApplicationPriorityIndicator(int v);
        FciDataBuilder& WithKernelIdentifier(int v);
        FciDataBuilder& WithExtendedSelection(unsigned char* v, int len);

        FciDataFactory Build();

    private:
        FciDataProperties fProperties;
    };
public:
    string toString();
    void copy(FciIssDataPtr p);
    FciIssData getData() {
        return this->fProperties.fciData;
    }


private:
    FciDataFactory(const FciDataProperties& properties) : fProperties(properties) {}

protected:

    FciDataProperties fProperties;
};

#endif  // _MODULAR_TEST_FCIDATA_FACTORY_H_
