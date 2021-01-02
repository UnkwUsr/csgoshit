#include "chams.h"
#include "interfaces.h"
#include "hooker.h"
#include <string>
#include <sstream>


ConVar* cv_chams;

IMaterial* materialFlat;

void Chams::Init() {
    cv_chams = 
}

void DrawPlayer(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld)
{
    C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
    if (!localplayer)
        return;

    C_BasePlayer* entity = (C_BasePlayer*) entityList->GetClientEntity(pInfo.entity_index);
    if (!entity)
        return;
    /* || entity->GetDormant() || !entity->GetAlive()) */

    if (entity == localplayer) {
        // this 'if' never happened. Why?
        return;
    }

    if (entity->GetTeam() == localplayer->GetTeam())
        return;

    modelRender->ForcedMaterialOverride(materialFlat);
    materialFlat->AlphaModulate(0.5f);

    // behind wall
    materialFlat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
    materialFlat->ColorModulate(1.0f, 0.0f, 0.0f);
    modelRenderVMT->GetOriginalMethod<DrawModelExecuteFn>(21)(thisptr, context, state, pInfo, pCustomBoneToWorld);

    // in front of wall
    materialFlat->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
    materialFlat->ColorModulate(0.0f, 1.0f, 0.0f);
    modelRenderVMT->GetOriginalMethod<DrawModelExecuteFn>(21)(thisptr, context, state, pInfo, pCustomBoneToWorld);
}

void Chams::DrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld)
{
    if (cv_chams->GetInt() == 0) {
        return;
    }

    if (!engine->IsInGame())
        return;

    if (!pInfo.pModel)
        return;

    static bool materialsCreated = false;
    if (!materialsCreated)
    {
        materialFlat = materialSystem->CreateMaterial("flat", KeyValuesFromString("UnlitGeneric", nullptr, nullptr));

        materialsCreated = true;
    }

    /* if (modelName.find("models/player") != std::string::npos) */
        DrawPlayer(thisptr, context, state, pInfo, pCustomBoneToWorld);
    /* else if (modelName.find("arms") != std::string::npos) */
    /*     DrawArms(pInfo); */
    /* else if (modelName.find("weapon") != std::string::npos) */
    /*     DrawWeapon(pInfo); */
}
