#include "ESP.h"
#include "..\Utils\Utils.h"
#include "..\SDK\IVEngineClient.h"
#include "..\SDK\PlayerInfo.h"

ESP g_ESP;

void ESP::RenderBox(C_BaseEntity* pEnt)
{
    Vector vecOrigin = pEnt->GetOrigin();
    Vector vecBottom = vecOrigin;
    vecBottom.z += (pEnt->GetFlags() & FL_DUCKING) ? 54.f : 72.f;

    Vector vecScreenBottom;
    if (!Utils::WorldToScreen(vecBottom, vecScreenBottom))
        return;

    Vector vecScreenOrigin;
    if (!Utils::WorldToScreen(vecOrigin, vecScreenOrigin))
        return;


    float sx = vecScreenOrigin.x;
    float sy = vecScreenOrigin.y;
    float h = vecScreenBottom.y - vecScreenOrigin.y;
    float w = h * 0.25f;

    /* Draw rect around the entity */
    g_Render.Rect(sx - w, sy, sx + w, sy + h, (pEnt->GetTeam() == localTeam) ? teamColor : enemyColor);

    /* Draw rect outline */
    g_Render.Rect(sx - w - 1, sy - 1, sx + w + 1, sy + h + 1, Color(0, 0, 0, 255));
    g_Render.Rect(sx - w + 1, sy + 1, sx + w - 1, sy + h - 1, Color(0, 0, 0, 255));
}

void ESP::RenderName(C_BaseEntity* pEnt, int iterator)
{
    PlayerInfo_t pInfo;
    g_pEngine->GetPlayerInfo(iterator, &pInfo);


    Vector vecPosition = pEnt->GetEyePosition(); vecPosition.z += 30;
    Vector vecScreenPos;
    if (!Utils::WorldToScreen(vecPosition, vecScreenPos))
        return;

    g_Render.String(vecScreenPos.x, vecScreenPos.y,
        CD3DFONT_CENTERED_X | CD3DFONT_DROPSHADOW,
        (localTeam == pEnt->GetTeam()) ? teamColor : enemyColor,
        g_Fonts.pFontTahoma10.get(), pInfo.szName);
}


void ESP::Render()
{
    if (!g::pLocalEntity)
        return;

    localTeam = g::pLocalEntity->GetTeam();

    for (int it = 1; it <= g_pEngine->GetMaxClients(); ++it)
    {
        C_BaseEntity* pPlayerEntity = g_pEntityList->GetClientEntity(it);

        // Sanity checks
        if (!pPlayerEntity
            || !pPlayerEntity->IsAlive()
            || pPlayerEntity->IsDormant()
            || pPlayerEntity == g::pLocalEntity)
            continue;

        if (g_Settings.bShowBoxes)
            this->RenderBox(pPlayerEntity);

        if (g_Settings.bShowNames)
            this->RenderName(pPlayerEntity, it);
    }
}
