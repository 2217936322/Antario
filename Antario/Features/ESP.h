#pragma once
#include "..\Utils\DrawManager.h"
#include "..\Utils\GlobalVars.h"
#include "..\Settings.h"


class ESP
{
public:
	void Render();
private:
	void RenderName(C_BaseEntity* pEnt, int iterator);

	int localTeam;
	Color teamColor{ 195, 240, 100, 255 };
	Color enemyColor{ 250, 165, 110, 255 };
};
extern ESP g_ESP;