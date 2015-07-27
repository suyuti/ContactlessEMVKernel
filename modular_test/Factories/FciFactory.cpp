#include <string.h> // memcpy
#include <stdio.h> // sprintf
#include <iostream>
#include <fstream>
#include <Emv/fci.h>

extern "C" {
    #include "Emv/fci.h"
}

#include "./FciFactory.h"

using namespace std;

FciFactory::FciBuilder& FciFactory::FciBuilder::WithFciData(const FciIssData &d)
{
    fProperties.fci._fciIssData[fProperties.fci._fciIssDataCount] = d;
    fProperties.fci._fciIssDataCount++;
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
