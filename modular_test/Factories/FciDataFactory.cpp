#include <string.h> // memcpy
#include <stdio.h> // sprintf
#include <iostream>
#include <fstream>
#include <Emv/fci.h>

extern "C" {
    #include "Emv/fci.h"
}

#include "./FciDataFactory.h"
#include "../testUtils.h"

using namespace std;

FciDataFactory::FciDataBuilder& FciDataFactory::FciDataBuilder::WithADFName(string adfName)
{
    if (adfName.size() < MAX_4F_LEN * 2) {
        int l = EmvTest::TestUtils::str2bcd(adfName, fProperties.fciData._4F+1);
        fProperties.fciData._4F[0] = (unsigned char)l;
    }
    return *this;
}

FciDataFactory::FciDataBuilder& FciDataFactory::FciDataBuilder::WithApplicationLabel(string label)
{
    if (label.size() < MAX_50_LEN * 2) {
        EmvTest::TestUtils::str2bcd(label, fProperties.fciData._50);
    }
    return *this;
}

FciDataFactory::FciDataBuilder& FciDataFactory::FciDataBuilder::WithApplicationPriorityIndicator(int v)
{
    fProperties.fciData._87[0] = 0x01;
    fProperties.fciData._87[1] = (unsigned char)v;
    return *this;
}

FciDataFactory::FciDataBuilder& FciDataFactory::FciDataBuilder::WithKernelIdentifier(int v)
{
    // TODO
    // fProperties.fciData._9F2A[0] = 0x00;
    // fProperties.fciData._9F2A[1] = 0x00;
    // fProperties.fciData._9F2A[1] = 0x00;
    return *this;
}

FciDataFactory::FciDataBuilder& FciDataFactory::FciDataBuilder::WithExtendedSelection(unsigned char *v, int len)
{
    // TODO
    return *this;
}

FciDataFactory FciDataFactory::FciDataBuilder::Build()
{
    return FciDataFactory(fProperties);
}

string FciDataFactory::toString()
{
    char tmp[255];
    string str = "";

    // sprintf(tmp, "Status Check        : %s\n", IS_STATUS_CHECK(fProperties.config.configData)== YES ? "YES" : "NO");
    // str.append(tmp);
    str.append(tmp);

    return str;
}

void FciDataFactory::copy(FciIssDataPtr p)
{
    if (!p) return;
    memcpy(p, &(fProperties.fciData), sizeof(FciIssData));
}
