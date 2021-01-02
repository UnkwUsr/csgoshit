#pragma once

#include "sdk.h"


typedef bool (*CreateMoveFn) (void*, float, CUserCmd*);

void setHooks();

namespace Hooks {
    bool CreateMove(void* thisptr, float flInputSampleTime, CUserCmd* cmd);
    void DrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld);
}

