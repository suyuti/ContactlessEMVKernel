
#ifndef _MODULAR_TEST_FCIDATA_FACTORY_H_
#define _MODULAR_TEST_FCIDATA_FACTORY_H_

#include <string>
#include <string.h> // memset
using namespace std;

extern "C" {
    #include "Emv/fci.h"
    #include "Common/kernelIdentifier.h"
}

class DirectoryEntryFactory {
private:
    class DirectoryEntryProperties {
    private:
        DirectoryEntryProperties() {
            memset(&directoryEntry, 0x00, sizeof(DirectoryEntry));
        }
        DirectoryEntry directoryEntry;

        friend class DirectoryEntryFactory;
        friend class DirectoryEntryBuilder;
    };
public:

    DirectoryEntryFactory() {}

    class DirectoryEntryBuilder {
    public:
        DirectoryEntryBuilder() {}
        DirectoryEntryBuilder& WithADFName(string adfName);
        DirectoryEntryBuilder& WithApplicationLabel(string label);
        DirectoryEntryBuilder& WithApplicationPriorityIndicator(int v);
        DirectoryEntryBuilder& WithKernelIdentifier(KernelIdentifier kid);
        DirectoryEntryBuilder& WithKernelIdentifierWithZeroLen();
        DirectoryEntryBuilder& WithExtendedSelection(unsigned char* v, int len);

        DirectoryEntryFactory Build();

    private:
        DirectoryEntryProperties fProperties;
    };
public:
    string toString();
    void copy(DirectoryEntryPtr p);
    DirectoryEntry getData() {
        return this->fProperties.directoryEntry;
    }


private:
    DirectoryEntryFactory(const DirectoryEntryProperties& properties) : fProperties(properties) {}

protected:

    DirectoryEntryProperties fProperties;
};

#endif  // _MODULAR_TEST_FCIDATA_FACTORY_H_
