#pragma once
#include "..\SDK\CInput.h"
#include "..\SDK\IVEngineClient.h"
#include "..\Settings.h"

class Misc
{
public:
    void OnCreateMove(CUserCmd* pCmd)
    {
        this->pCmd = pCmd;
        this->pLocal = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer()); // To be replaced with a global var
        if (this->pLocal)
        {
            if (g_Settings.bBhopEnabled)
                this->DoBhop();
            // sum future shit
        }
    }
private:
    CUserCmd* pCmd;
    C_BaseEntity* pLocal;

    void DoBhop()
    {
        if (!(this->pLocal->GetFlags() & EntityFlags::FL_ONGROUND) && this->pLocal->GetMoveType() != MoveType_t::MOVETYPE_LADDER)
            if (this->pCmd->buttons & IN_JUMP)
                this->pCmd->buttons &= ~IN_JUMP;
    }
};
extern Misc g_Misc;
