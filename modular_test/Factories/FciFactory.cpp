#include <string.h> // memcpy
#include <stdio.h> // sprintf
#include <iostream>
#include <fstream>

extern "C" {
    #include "Emv/fci.h"
}

#include "./FciFactory.h"

using namespace std;

FciFactory::FciBuilder& FciFactory::FciBuilder::WithDirectoryEntry(const DirectoryEntry &d)
{
    fProperties.fci._directoryEntry[fProperties.fci._directoryEntryCount] = d;
    fProperties.fci._directoryEntryCount++;
    return *this;
}

FciFactory FciFactory::FciBuilder::Build()
{
    return FciFactory(fProperties);
}

string FciFactory::toString()
{
    char tmp[255];
    string str = "";

    // sprintf(tmp, "Status Check        : %s\n", IS_STATUS_CHECK(fProperties.config.configData)== YES ? "YES" : "NO");
    // str.append(tmp);
    str.append(tmp);

    return str;
}

void FciFactory::copy(FciPtr p)
{
    if (!p) return;
    memcpy(p, &(fProperties.fci), sizeof(Fci));
}
