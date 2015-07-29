#include "./readerManager.h"
#include "../Common/hal.h"
#include "../EntryPoint/entryPoint.h"

typedef struct {
    int             kid;
    _performKernel  performKernel;
} KernelMap;

static KernelMap gKernels[10] = {0x00};
static int gKernelCount = 0;

//-----------------------------------------------------------------------------

int registerKernel(int kid, _performKernel hadler)
{
    if (gKernelCount > sizeof(gKernels)/ sizeof(KernelMap)) {
        return -1;
    }
    gKernels[gKernelCount].kid = kid;
    gKernels[gKernelCount].performKernel = hadler;
    gKernelCount++;
    return gKernelCount;
}

//-----------------------------------------------------------------------------

int on_card_detected(void)
{
    ep_process(0, 0);
    return 0;
}

//-----------------------------------------------------------------------------

int act()
{
    // 1. start polling
    poll(&on_card_detected);

    // 2. display ready
    displayMessage("READY");
    return 0;
}
