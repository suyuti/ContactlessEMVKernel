#include "./readerManager.h"
#include "../Kernel/Paypass/paypass.h"


int main(int argc, char** argv)
{
    registerKernel(1, &paypass);
    registerKernel(2, &paypass);

    act();
    return 0;
}