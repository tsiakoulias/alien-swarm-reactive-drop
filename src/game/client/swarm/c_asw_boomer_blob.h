#pragma once

#include "c_asw_grenade_vindicator.h"

class C_ASW_Boomer_Blob : public C_ASW_Grenade_Vindicator
{
	DECLARE_CLASS( C_ASW_Boomer_Blob, C_ASW_Grenade_Vindicator );
	DECLARE_CLIENTCLASS();

public:
	virtual void Detonate();
	virtual void CreateSmokeTrail();
};