#include "cbase.h"
#include "c_asw_grenade_freeze.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IMPLEMENT_CLIENTCLASS_DT( C_ASW_Grenade_Freeze, DT_ASW_Grenade_Freeze, CASW_Grenade_Freeze )
	
END_RECV_TABLE();

void C_ASW_Grenade_Freeze::CreateSmokeTrail()
{
	if ( m_pSmokeTrail )
		return;

	m_pSmokeTrail = ParticleProp()->Create( "grenade_freeze_main_trail", PATTACH_ABSORIGIN_FOLLOW, -1, Vector( 0, 0, 0 ) );
}

void C_ASW_Grenade_Freeze::Detonate()
{
	
}

