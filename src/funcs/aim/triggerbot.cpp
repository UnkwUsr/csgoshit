#include "triggerbot.h"
#include "interfaces.h"
#include "Utils/math.h"
#include <chrono>


long GetEpochTime()
{
    auto duration = std::chrono::system_clock::now().time_since_epoch();

    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

void Triggerbot::CreateMove(CUserCmd* cmd) {
    C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
    if (!localplayer || !localplayer->GetAlive())
        return;

    if (localplayer->GetFlashBangTime() - globalVars->curtime > 2.0f)
        return;

    long currentTime_ms = GetEpochTime();
    static long timeStamp = currentTime_ms;
    long oldTimeStamp;

    Vector traceStart, traceEnd;

    QAngle viewAngles;
    engine->GetViewAngles(viewAngles);
    QAngle viewAngles_rcs = viewAngles + *localplayer->GetAimPunchAngle() * 2.0f;

    Math::AngleVectors(viewAngles_rcs, traceEnd);

    traceStart = localplayer->GetEyePosition();
    traceEnd = traceStart + (traceEnd * 8192.0f);

    trace_t tr;
    /* if (Settings::Triggerbot::Filters::walls) */
    /* { */
    /*     Autowall::FireBulletData data; */
    /*     if (Autowall::GetDamage(traceEnd, !Settings::Triggerbot::Filters::allies, data) == 0.0f) */
    /*         return; */

    /*     tr = data.enter_trace; */
    /* } */
    /* else */
    {
        Ray_t ray;
        ray.Init(traceStart, traceEnd);
        CTraceFilter traceFilter;
        traceFilter.pSkip = localplayer;
        trace->TraceRay(ray, 0x46004003, &traceFilter, &tr);
    }

    oldTimeStamp = timeStamp;
    timeStamp = currentTime_ms;

    C_BasePlayer* player = (C_BasePlayer*) tr.m_pEntityHit;
    if (!player)
        return;

    // this check is not work, but it exist in original code
    /* if (player->GetClientClass()->m_ClassID != EClassIds::CCSPlayer) */
    /*     return; */

    if (player == localplayer
            || player->GetDormant()
            || !player->GetAlive()
            || player->GetImmune())
        return;

    /* if (player->GetTeam() != localplayer->GetTeam() && !Settings::Triggerbot::Filters::enemies) */
    /*     return; */

    if (player->GetTeam() == localplayer->GetTeam())
        return;

    bool filter = false;
    switch(tr.hitgroup) {
        /* case HitGroups::HITGROUP_HEAD: */
        /* case HitGroups::HITGROUP_CHEST: */
        /* case HitGroups::HITGROUP_STOMACH: */
            filter = true;
            break;
    }
    if (!filter) {
        return;
    }

    // TODO: should consider smoke
    /* if (Settings::Triggerbot::Filters::smokeCheck && LineGoesThroughSmoke(tr.startpos, tr.endpos, 1)) */
    /*     return; */

    C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
    if (!activeWeapon || activeWeapon->GetAmmo() == 0)
        return;

    /* ItemDefinitionIndex itemDefinitionIndex = *activeWeapon->GetItemDefinitionIndex(); */
    /* if (itemDefinitionIndex == ItemDefinitionIndex::WEAPON_KNIFE || itemDefinitionIndex >= ItemDefinitionIndex::WEAPON_KNIFE_BAYONET) */
    /*     return; */

    // TODO: should consider grenade in hands
    /* CSWeaponType weaponType = activeWeapon->GetCSWpnData()->GetWeaponType(); */
    /* if (weaponType == CSWeaponType::WEAPONTYPE_C4 || weaponType == CSWeaponType::WEAPONTYPE_GRENADE) */
    /*     return; */

    if (activeWeapon->GetNextPrimaryAttack() > globalVars->curtime)
    {
        /* if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER) */
        /*     cmd->buttons &= ~IN_ATTACK2; */
        /* else */
        cmd->buttons &= ~IN_ATTACK;
    }
    else
    {
        /* if (Settings::Triggerbot::Delay::enabled && currentTime_ms - oldTimeStamp < Settings::Triggerbot::Delay::value) */
        /* { */
        /*     timeStamp = oldTimeStamp; */
        /*     return; */
        /* } */

        /* if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER) */
        /*     cmd->buttons |= IN_ATTACK2; */
        /* else */
        cmd->buttons |= IN_ATTACK;
    }

    timeStamp = currentTime_ms;
}

