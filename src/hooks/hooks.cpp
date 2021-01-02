#include "hooks.h"
#include "hooker.h"

void setHooks() {
    modelRenderVMT->HookVM((void*) Hooks::DrawModelExecute, 21);
    modelRenderVMT->ApplyVMT();

    clientModeVMT->HookVM((void*) Hooks::CreateMove, 25);
    clientModeVMT->ApplyVMT();
}

