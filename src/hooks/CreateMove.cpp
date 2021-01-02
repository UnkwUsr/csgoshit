#include "hooks/hooks.h"
#include "hooker.h"
#include "funcs/movement/bhop.h"
#include "funcs/aim/triggerbot.h"


bool Hooks::CreateMove(void* thisptr, float flInputSampleTime, CUserCmd* cmd)
{
    clientModeVMT->GetOriginalMethod<CreateMoveFn>(25)(thisptr, flInputSampleTime, cmd);

    if (cmd && cmd->command_number)
    {
        Bhop::CreateMove(cmd);
        /* Triggerbot::CreateMove(cmd); */
    }

    return false;
}
