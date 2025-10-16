#include "cbase.h"
#include "func_asw_fade.h"
#include "asw_shareddefs.h"
#include "asw_fade_proxy_shared.h"
#include "asw_inhabitable_npc.h"
#include "asw_player.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

LINK_ENTITY_TO_CLASS( func_asw_fade, CFunc_ASW_Fade );

BEGIN_DATADESC( CFunc_ASW_Fade )
	DEFINE_FIELD( m_bHasProxies, FIELD_BOOLEAN ),
	DEFINE_KEYFIELD( m_nFadeOpacity, FIELD_CHARACTER, "fade_opacity" ),
	DEFINE_KEYFIELD( m_iCollideWithGrenades, FIELD_CHARACTER, "CollideWithGrenades" ),
	DEFINE_KEYFIELD( m_bCollideWithMarines, FIELD_BOOLEAN, "CollideWithMarines" ),
	DEFINE_INPUT( m_bAllowFade, FIELD_BOOLEAN, "AllowFade" ),
	DEFINE_INPUTFUNC( FIELD_INTEGER, "SetCollideWithGrenades", InputSetCollideWithGrenades ),
	DEFINE_INPUTFUNC( FIELD_BOOLEAN, "SetCollideWithMarines", InputSetCollideWithMarines ),
END_DATADESC()

IMPLEMENT_SERVERCLASS_ST( CFunc_ASW_Fade, DT_Func_ASW_Fade )
	SendPropInt( SENDINFO( m_nFadeOpacity ), 8, SPROP_UNSIGNED ),
	SendPropInt( SENDINFO( m_iCollideWithGrenades ), 2, SPROP_UNSIGNED ),
	SendPropBool( SENDINFO( m_bCollideWithMarines ) ),
	SendPropBool( SENDINFO( m_bAllowFade ) ),
	SendPropBool( SENDINFO( m_bHasProxies ) ),
END_SEND_TABLE()

CFunc_ASW_Fade::CFunc_ASW_Fade()
{
	m_bHasProxies = false;
	m_iCollideWithGrenades = 0;
	m_bCollideWithMarines = true;
	m_nFadeOpacity = 0;
	m_bAllowFade = true;
}

void CFunc_ASW_Fade::Spawn()
{
	BaseClass::Spawn();

	SetCollisionGroup( COLLISION_GROUP_NONE );
	Assert( m_iCollideWithGrenades <= 2 );
}

void CFunc_ASW_Fade::DisableCollisionsWithGrenade( CBaseEntity* pGrenade )
{
	const float flGrenadeZ = pGrenade->GetAbsOrigin().z;
	const string_t iszClassName = AllocPooledString( "func_asw_fade" );

	CFunc_ASW_Fade* pCeiling = nullptr;
	while ( ( pCeiling = assert_cast<CFunc_ASW_Fade*>(
		gEntList.FindEntityByClassnameFast( pCeiling, iszClassName ) ) ) != nullptr )
	{
		const bool bShouldDisable =
			( pCeiling->m_iCollideWithGrenades == 0 && pCeiling->GetAbsOrigin().z >= flGrenadeZ ) ||
			( pCeiling->m_iCollideWithGrenades == 2 );

		const bool bCurrentlyDisabled = PhysEntityCollisionsAreDisabled( pCeiling, pGrenade );

		if ( bShouldDisable && !bCurrentlyDisabled )
		{
			PhysDisableEntityCollisions( pCeiling, pGrenade );
		}
		else if ( !bShouldDisable && bCurrentlyDisabled )
		{
			PhysEnableEntityCollisions( pCeiling, pGrenade );
		}
	}
}

void CFunc_ASW_Fade::DisableCollisionsWithMarine( CBaseEntity* pMarine )
{
	const string_t iszClassName = AllocPooledString( "func_asw_fade" );

	CFunc_ASW_Fade* pCeiling = nullptr;
	while ( ( pCeiling = assert_cast<CFunc_ASW_Fade*>(
		gEntList.FindEntityByClassnameFast( pCeiling, iszClassName ) ) ) != nullptr )
	{
		const bool bShouldDisable = !pCeiling->m_bCollideWithMarines;
		const bool bCurrentlyDisabled = PhysEntityCollisionsAreDisabled( pCeiling, pMarine );

		if ( bShouldDisable && !bCurrentlyDisabled )
		{
			PhysDisableEntityCollisions( pCeiling, pMarine );
		}
		else if ( !bShouldDisable && bCurrentlyDisabled )
		{
			PhysEnableEntityCollisions( pCeiling, pMarine );
		}
	}
}


void CFunc_ASW_Fade::InputSetCollideWithGrenades( inputdata_t& inputdata )
{
	m_iCollideWithGrenades = clamp( inputdata.value.Int(), 0, 2 );

	static const char* pszExplosiveClasses[] = {
		"asw_mine",
		"npc_grenade_frag",
		"asw_rocket",
        "grenadespit",
		"asw_missile_round",
		"asw_grenade_cluster",
		"asw_flare_projectile",
		"asw_laser_mine",
		"asw_grenade_vindicator",
		"asw_gas_grenade_projectile",
		nullptr
	};

	for ( const char** pszClass = pszExplosiveClasses; *pszClass; ++pszClass )
	{
		CBaseEntity* pGrenade = NULL;
		while ( ( pGrenade = gEntList.FindEntityByClassname( pGrenade, *pszClass ) ) != NULL )
		{
			DisableCollisionsWithGrenade( pGrenade );
		}
	}
}

void CFunc_ASW_Fade::InputSetCollideWithMarines( inputdata_t& inputdata )
{
	m_bCollideWithMarines = !!inputdata.value.Int();

	CBaseEntity* pMarine = NULL;
	while ( ( pMarine = gEntList.FindEntityByClassname( pMarine, "asw_marine" ) ) != NULL )
	{
		DisableCollisionsWithMarine( pMarine );
	}
}

bool CFunc_ASW_Fade::ShouldFade( CASW_Inhabitable_NPC *pNPC )
{
	if ( !m_bAllowFade || !pNPC || !pNPC->IsInhabited() || !pNPC->GetCommander() )
	{
		return false;
	}

	if ( pNPC->GetCommander()->GetASWControls() == ASWC_TOPDOWN )
	{
		if ( m_bHasProxies )
		{
			Vector vecEyePosition = pNPC->EyePosition();

#ifdef DBGFLAG_ASSERT
			bool bAtLeastOneProxy = false;
#endif
			for ( CBaseEntity *pEnt = FirstMoveChild(); pEnt; pEnt = pEnt->NextMovePeer() )
			{
				CPoint_ASW_Fade_Proxy *pProxy = dynamic_cast< CPoint_ASW_Fade_Proxy * >( pEnt );
				if ( pProxy )
				{
					if ( pProxy->ShouldFade( vecEyePosition ) )
					{
						return true;
					}

#ifdef DBGFLAG_ASSERT
					bAtLeastOneProxy = true;
#endif
				}
			}

			Assert( bAtLeastOneProxy );

			return false;
		}

		return pNPC->GetAbsOrigin().z < GetAbsOrigin().z;
	}

	return false;
}
