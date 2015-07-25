#include <string.h> // memcpy
#include <stdio.h> // sprintf
#include <iostream>
#include <fstream>

extern "C" {
    #include "EntryPoint/epCommon.h"
    #include "EntryPoint/epIndicators.h"
}

#include "configFactory.h"

using namespace std;

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithStatusCheck(unsigned char v)
{
    //fProperties.config.statusCheck = v;
    if (v == YES) {
        SET_STATUS_CHECK(fProperties.config.configData);
    }
    else {
        RESET_STATUS_CHECK(fProperties.config.configData);
    }
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithZeroAmountAllowed(unsigned char v)
{
    fProperties.config.configData.zeroAmountAllowed = v;
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithClessTrnxLimit(int v)
{
    fProperties.config.configData.clessTrnxLimit = v;
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithClessFloorLimit(int v)
{
    fProperties.config.configData.clessFloorLimit = v;
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithTermFloorLimit(int v)
{
    fProperties.config.configData.termFloorLimit = v;
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithCvmRequiredLimit(int v)
{
    fProperties.config.configData.cvmRequiredLimit = v;
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithTtq(string v)
{
    // TODO
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithTtq(unsigned char v[4])
{
    memcpy(fProperties.config.configData.ttq, v, 4);
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithExtendedSelectionSupport(unsigned char v)
{
    fProperties.config.configData.extendedSelectionSupport = v;
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithAid(string aid)
{
    strcpy(fProperties.config.aid, aid.c_str());
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithKernelId(unsigned char kid)
{
    fProperties.config.kid = kid;
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithStatusCheckTequested(bool v)
{
    if (v)
        SET_EPIND_STATUS_CHECK_REQ(fProperties.config.indicators);
    else
        RESET_EPIND_STATUS_CHECK_REQ(fProperties.config.indicators);

    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithClessAppNotAllowed(bool v)
{
    if (v)
        SET_EPIND_CLESS_APP_NOT_ALLOWED(fProperties.config.indicators);
    else
        RESET_EPIND_CLESS_APP_NOT_ALLOWED(fProperties.config.indicators);

    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithZeroAmount(bool v)
{
    if (v)
        SET_EPIND_ZERO_AMOUNT(fProperties.config.indicators);
    else
        RESET_EPIND_ZERO_AMOUNT(fProperties.config.indicators);
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithReaderCVMReqLimitExceeded(bool v)
{
    if (v)
        SET_EPIND_READER_CVM_REQ_LIMIT_EXCEEDED(fProperties.config.indicators);
    else
        RESET_EPIND_READER_CVM_REQ_LIMIT_EXCEEDED(fProperties.config.indicators);
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithReaderClessFloorLimitExceeded(bool v)
{
    if (v)
        SET_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(fProperties.config.indicators);
    else
        RESET_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(fProperties.config.indicators);
    return *this;
}

TerminalConfigs::TerminalConfigBuilder& TerminalConfigs::TerminalConfigBuilder::WithCopyTtq(bool v)
{
    // TODO
    return *this;
}


TerminalConfigs TerminalConfigs::TerminalConfigBuilder::Build()
{
    return TerminalConfigs(fProperties);
}

string TerminalConfigs::toString()
{
    char tmp[255];
    string str = "";

    sprintf(tmp, "Status Check        : %s\n", IS_STATUS_CHECK(fProperties.config.configData)== YES ? "YES" : "NO");
    str.append(tmp);

    sprintf(tmp, "Zero Amount Allowed : %s\n", fProperties.config.configData.zeroAmountAllowed == YES ? "YES" : "NO");
    str.append(tmp);

    sprintf(tmp, "Cless Trnx Limit    : %d\n", fProperties.config.configData.clessTrnxLimit);
    str.append(tmp);

    sprintf(tmp, "Cless Floor Limit   : %d\n", fProperties.config.configData.clessFloorLimit);
    str.append(tmp);

    sprintf(tmp, "Terminal Floor Limit: %d\n", fProperties.config.configData.termFloorLimit);
    str.append(tmp);

    sprintf(tmp, "CVM Required Limit  : %d\n", fProperties.config.configData.cvmRequiredLimit);
    str.append(tmp);

    sprintf(tmp, "TTQ                 : %02X %02X %02X %02X\n",
            fProperties.config.configData.ttq[0],
            fProperties.config.configData.ttq[1],
            fProperties.config.configData.ttq[2],
            fProperties.config.configData.ttq[3]);

    // TODO Extended selection Support

    str.append(tmp);

    return str;
}

void TerminalConfigs::save(string name)
{
    ofstream file;
    file.open(name.c_str());
    file.close();
}
