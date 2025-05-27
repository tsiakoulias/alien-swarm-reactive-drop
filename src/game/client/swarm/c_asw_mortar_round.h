#pragma once

#include "cbase.h"
#include "c_asw_grenade_vindicator.h"

class C_ASW_Mortar_Round : public C_ASW_Grenade_Vindicator
{
	DECLARE_CLASS( C_ASW_Mortar_Round, C_ASW_Grenade_Vindicator );
	DECLARE_CLIENTCLASS();

public:
	virtual void Detonate();
	virtual void CreateSmokeTrail();
};
