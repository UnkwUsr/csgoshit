#include "hooks.h"
#include "interfaces.h"
#include "hooker.h"
#include "sdk.h"
#include "funcs/visuals/chams.h"

void Hooks::DrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld)
{
    if (!engine->IsTakingScreenshot())
    {
        Chams::DrawModelExecute(thisptr, context, state, pInfo, pCustomBoneToWorld);
    }

    modelRenderVMT->GetOriginalMethod<DrawModelExecuteFn>(21)(thisptr, context, state, pInfo, pCustomBoneToWorld);
    modelRender->ForcedMaterialOverride(NULL);
}

