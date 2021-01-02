/* #include "main.h" */
/* #include "utils/mem/mem.h" */
/* #include "hack.h" */
#include <dlfcn.h>
#include <iostream>
#include "interfaces.h"
#include "hooker.h"
#include "hooks/hooks.h"
#include "offsets.h"
#include "funcs/funcs.h"


__attribute__((constructor))
void on_load()
{
    findInterfaces();
    // dumpInterfaces(); // will be useful for debug

    Hooker::InitializeVMHooks();
    Hooker::FindIClientMode();
    Hooker::FindGlobalVars();
    Hooker::FindKeyValueFromString();

    setHooks();

    /* NetVarManager::DumpNetvars(); */ // will be useful for debug
    Offsets::GetOffsets();

    InitFuncs();

    cvar->ConsoleColorPrintf(ColorRGBA(150, 150, 0), "csgoshit loaded fine\n");
}

__attribute__((destructor))
void on_un_load()
{
    clientModeVMT->ReleaseVMT();
    modelRenderVMT->ReleaseVMT();

    /* Hack_Terminate(); */
    cvar->ConsoleColorPrintf(ColorRGBA(150, 150, 0), "csgoshit UNloaded fine\n");
}
