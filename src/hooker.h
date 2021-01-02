#pragma once

#include "Utils/vmt.h"
#include "sdk.h"


extern VMT* clientModeVMT;
extern VMT* modelRenderVMT;

typedef void (*DrawModelExecuteFn) (void*, void*, void*, const ModelRenderInfo_t&, matrix3x4_t*);

namespace Hooker {
    void InitializeVMHooks();

    void FindIClientMode();
    void FindGlobalVars();

    void FindKeyValueFromString();
}

#define KEYVALUESFROMSTRING_SIGNATURE "\x55\x48\x89\xe5\x41\x57\x41\x56\x41\x55\x41\x54\x49\x89\xfc\x53\x48\x89\xf3\x48\x81\xec\x38\x05"
#define KEYVALUESFROMSTRING_MASK "xxxxxxxxxxxxxxxxxxxxxxxx"
