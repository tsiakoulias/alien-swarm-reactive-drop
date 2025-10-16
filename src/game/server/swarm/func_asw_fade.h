#ifndef _INCLUDED_FUNC_ASW_FADE_H
#define _INCLUDED_FUNC_ASW_FADE_H
#ifdef _WIN32
#pragma once
#endif

#include "modelentities.h"

class CASW_Inhabitable_NPC;

class CFunc_ASW_Fade : public CFuncBrush
{
public:
	DECLARE_CLASS( CFunc_ASW_Fade, CFuncBrush );

	DECLARE_DATADESC();
	DECLARE_SERVERCLASS();

	CFunc_ASW_Fade();

	virtual void Spawn() override;
	bool ShouldFade( CASW_Inhabitable_NPC *pNPC );

	static void ApplyGrenadeCollisionRules( CBaseEntity *pGrenade );
	static void ApplyMarineCollisionRules( CBaseEntity *pMarine );

	void SetGrenadeCollisionRules( inputdata_t& inputdata );
	void SetMarineCollisionRules( inputdata_t& inputdata );

	CNetworkVar( bool, m_bHasProxies );
	// 0 = only when grenade spawns above the brush
	// 1 = always
	// 2 = never
	CNetworkVar( byte, m_iCollideWithGrenades );
	CNetworkVar( bool, m_bCollideWithMarines );
	CNetworkVar( byte, m_nFadeOpacity );
	CNetworkVar( bool, m_bAllowFade );
};


#endif // _INCLUDED_FUNC_ASW_FADE_H
