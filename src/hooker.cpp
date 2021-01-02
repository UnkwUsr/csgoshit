#include "hooker.h"
#include "interfaces.h"
#include "Utils/patternfinder.h"


VMT* clientModeVMT;
VMT* modelRenderVMT;

IClientMode* clientMode;

KeyValuesFromStringFn KeyValuesFromString;

void Hooker::InitializeVMHooks() {
    modelRenderVMT = new VMT(modelRender);
}

inline uintptr_t GetAbsoluteAddress(uintptr_t instruction_ptr, int offset, int size)
{
    return instruction_ptr + *reinterpret_cast<uint32_t*>(instruction_ptr + offset) + size;
};


void Hooker::FindIClientMode()
{
    typedef IClientMode* (*GetClientModeFn) (void);

    uintptr_t hudprocessinput = reinterpret_cast<uintptr_t>(getvtable(client)[10]);
    GetClientModeFn GetClientMode = reinterpret_cast<GetClientModeFn>(GetAbsoluteAddress(hudprocessinput + 11, 1, 5));

    clientMode = GetClientMode();
    clientModeVMT = new VMT(clientMode);
}

void Hooker::FindGlobalVars()
{
    uintptr_t HudUpdate = reinterpret_cast<uintptr_t>(getvtable(client)[11]);

    globalVars = *reinterpret_cast<CGlobalVars**>(GetAbsoluteAddress(HudUpdate + 13, 3, 7));
}

void Hooker::FindKeyValueFromString()
{
    uintptr_t func_address = PatternFinder::FindPatternInModule("/materialsystem_client.so", (unsigned char*) KEYVALUESFROMSTRING_SIGNATURE, KEYVALUESFROMSTRING_MASK);
    KeyValuesFromString = reinterpret_cast<KeyValuesFromStringFn>(func_address);
}
