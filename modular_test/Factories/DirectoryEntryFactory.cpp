#include <string.h> // memcpy
#include <stdio.h> // sprintf
#include <iostream>
#include <fstream>
#include <Emv/fci.h>

extern "C" {
    #include "Emv/fci.h"
}

#include "./DirectoryEntryFactory.h"
#include "../testUtils.h"
#include "../../modular_src/Emv/fci.h"

using namespace std;

DirectoryEntryFactory::DirectoryEntryBuilder& DirectoryEntryFactory::DirectoryEntryBuilder::WithADFName(string adfName)
{
    if (adfName.size() < MAX_4F_LEN * 2) {
        int l = EmvTest::TestUtils::str2bcd(adfName, fProperties.directoryEntry._4F+1);
        fProperties.directoryEntry._4F[0] = (unsigned char)l;
    }
    return *this;
}

DirectoryEntryFactory::DirectoryEntryBuilder& DirectoryEntryFactory::DirectoryEntryBuilder::WithApplicationLabel(string label)
{
    if (label.size() < MAX_50_LEN * 2) {
        EmvTest::TestUtils::str2bcd(label, fProperties.directoryEntry._50);
    }
    return *this;
}

DirectoryEntryFactory::DirectoryEntryBuilder& DirectoryEntryFactory::DirectoryEntryBuilder::WithApplicationPriorityIndicator(int v)
{
    fProperties.directoryEntry._87[0] = 0x01;
    fProperties.directoryEntry._87[1] = (unsigned char)v;
    return *this;
}

DirectoryEntryFactory::DirectoryEntryBuilder& DirectoryEntryFactory::DirectoryEntryBuilder::WithKernelIdentifier(KernelIdentifier kid)
{
    fProperties.directoryEntry._9F2A[0] = 8;
    memcpy(fProperties.directoryEntry._9F2A+1, kid, sizeof(KernelIdentifier));

    return *this;
}

DirectoryEntryFactory::DirectoryEntryBuilder& DirectoryEntryFactory::DirectoryEntryBuilder::WithKernelIdentifierWithZeroLen()
{
    fProperties.directoryEntry._9F2A[0] = 0;

    return *this;
}

DirectoryEntryFactory::DirectoryEntryBuilder& DirectoryEntryFactory::DirectoryEntryBuilder::WithExtendedSelection(unsigned char *v, int len)
{
    // TODO
    return *this;
}

DirectoryEntryFactory DirectoryEntryFactory::DirectoryEntryBuilder::Build()
{
    return DirectoryEntryFactory(fProperties);
}

string DirectoryEntryFactory::toString()
{
    char tmp[255];
    string str = "";

    // sprintf(tmp, "Status Check        : %s\n", IS_STATUS_CHECK(fProperties.config.configData)== YES ? "YES" : "NO");
    // str.append(tmp);
    str.append(tmp);

    return str;
}

void DirectoryEntryFactory::copy(DirectoryEntryPtr p)
{
    if (!p) return;
    memcpy(p, &(fProperties.directoryEntry), sizeof(DirectoryEntry));
}
