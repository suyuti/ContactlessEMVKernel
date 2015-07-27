#include <string.h> // memcpy
#include <stdio.h> // sprintf
#include <iostream>
#include <fstream>
#include <EntryPoint/epCommon.h>

extern "C" {
    #include "EntryPoint/epCommon.h"
    #include "EntryPoint/epIndicators.h"
}

#include "EntryPointConfigFactory.h"
#include "../testUtils.h"

using namespace std;

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithStatusCheck(unsigned char v)
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

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithZeroAmountAllowed(unsigned char v)
{
    fProperties.config.configData.zeroAmountAllowed = v;
    return *this;
}

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithClessTrnxLimit(int v)
{
    fProperties.config.configData.clessTrnxLimit = v;
    return *this;
}

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithClessFloorLimit(int v)
{
    fProperties.config.configData.clessFloorLimit = v;
    return *this;
}

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithTermFloorLimit(int v)
{
    fProperties.config.configData.termFloorLimit = v;
    return *this;
}

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithCvmRequiredLimit(int v)
{
    fProperties.config.configData.cvmRequiredLimit = v;
    return *this;
}

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithTtq(string v)
{
    // TODO
    return *this;
}

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithTtq(unsigned char v[4])
{
    memcpy(fProperties.config.configData.ttq, v, 4);
    return *this;
}

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithExtendedSelectionSupport(unsigned char v)
{
    fProperties.config.configData.extendedSelectionSupport = v;
    return *this;
}

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithAid(string aid)
{
    if (aid.size() < 20 * 2) {
        int l = EmvTest::TestUtils::str2bcd(aid, (unsigned char*)fProperties.config.aid+1);
        fProperties.config.aid[0] = (unsigned char)l;
    }
    return *this;
}

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithKernelId(unsigned char kid)
{
    fProperties.config.kid = kid;
    return *this;
}

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithStatusCheckTequested(bool v)
{
    if (v)
        SET_EPIND_STATUS_CHECK_REQ(fProperties.config.indicators);
    else
        RESET_EPIND_STATUS_CHECK_REQ(fProperties.config.indicators);

    return *this;
}

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithClessAppNotAllowed()
{
    SET_EPIND_CLESS_APP_NOT_ALLOWED(fProperties.config.indicators);

    return *this;
}

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithZeroAmount(bool v)
{
    if (v)
        SET_EPIND_ZERO_AMOUNT(fProperties.config.indicators);
    else
        RESET_EPIND_ZERO_AMOUNT(fProperties.config.indicators);
    return *this;
}

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithReaderCVMReqLimitExceeded(bool v)
{
    if (v)
        SET_EPIND_READER_CVM_REQ_LIMIT_EXCEEDED(fProperties.config.indicators);
    else
        RESET_EPIND_READER_CVM_REQ_LIMIT_EXCEEDED(fProperties.config.indicators);
    return *this;
}

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithReaderClessFloorLimitExceeded(bool v)
{
    if (v)
        SET_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(fProperties.config.indicators);
    else
        RESET_EPIND_READER_CLESS_FLOOR_LIMIT_EXCEEDED(fProperties.config.indicators);
    return *this;
}

EntryPointConfigs::EntryPointConfigBuilder& EntryPointConfigs::EntryPointConfigBuilder::WithCopyTtq(bool v)
{
    // TODO
    return *this;
}


EntryPointConfigs EntryPointConfigs::EntryPointConfigBuilder::Build()
{
    return EntryPointConfigs(fProperties);
}

string EntryPointConfigs::toString()
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

void EntryPointConfigs::save(string name)
{
    ofstream file;
    file.open(name.c_str());
    file.close();
}

void EntryPointConfigs::copy(EpConfigPtr p)
{
    if (!p) return;
    memcpy(p, &(this->fProperties.config), sizeof(EpConfig));
}
