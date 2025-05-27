#ifndef _INCLUDED_C_ASW_GRENADE_VINDICATOR_H
#define _INCLUDED_C_ASW_GRENADE_VINDICATOR_H

#pragma once

#include "c_asw_rifle_grenade.h"

class C_ASW_Grenade_Vindicator : public C_ASW_Rifle_Grenade
{
	DECLARE_CLASS( C_ASW_Grenade_Vindicator, C_ASW_Rifle_Grenade );
	DECLARE_CLIENTCLASS();

public:
	C_ASW_Grenade_Vindicator();
	virtual void Spawn();
	virtual void OnDataChanged(DataUpdateType_t updateType);
	virtual void Detonate();
	virtual void CreateSmokeTrail();

	bool m_bDetonated;

	CNetworkVector( m_vecDetonateOrigin );

	CUtlReference<CNewParticleEffect> m_pSmokeTrail;
};

#endif	// _INCLUDED_C_ASW_GRENADE_VINDICATOR_H
