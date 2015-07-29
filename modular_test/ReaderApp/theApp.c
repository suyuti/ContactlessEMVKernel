#include "Common/hal.h"
#include "../defaultHalImpl.h"

int main(int argc, char** argv)
{
    setRfOpen(&defaultRfOpen);
    setRfClose(&defaultRfClose);
    setPoll(&defaultPoll);

    setDisplayMessage(&defaultDisplayMessage);

    act();

    return 0;
}