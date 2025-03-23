#include "cbase.h"
#include "c_asw_grenade_vindicator.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IMPLEMENT_NETWORKCLASS_ALIASED( ASW_Grenade_Vindicator, DT_ASW_Grenade_Vindicator )

BEGIN_NETWORK_TABLE( C_ASW_Grenade_Vindicator, DT_ASW_Grenade_Vindicator )
	RecvPropVector( RECVINFO( m_vecDetonateOrigin ) ),
END_NETWORK_TABLE()


C_ASW_Grenade_Vindicator::C_ASW_Grenade_Vindicator()
{
	m_bDetonated = false;
	m_pSmokeTrail = NULL;
	m_vecDetonateOrigin = Vector( 0.0, 0.0, 0.0 );
}

void C_ASW_Grenade_Vindicator::Spawn()
{
	CreateSmokeTrail();
}

void C_ASW_Grenade_Vindicator::OnDataChanged(DataUpdateType_t updateType)
{
	if ( updateType == DATA_UPDATE_DATATABLE_CHANGED )
	{
		if ( !m_bDetonated && m_vecDetonateOrigin != Vector( 0.0, 0.0, 0.0 ) )
		{
			Detonate();
			m_bDetonated = true;
		}
	}
}

void C_ASW_Grenade_Vindicator::CreateSmokeTrail()
{
	if ( m_pSmokeTrail )
		return;

	m_pSmokeTrail = ParticleProp()->Create( "rocket_trail_small", PATTACH_ABSORIGIN_FOLLOW, -1, Vector( 0, 0, 0 ) );
}

void C_ASW_Grenade_Vindicator::Detonate()
{
	if ( m_pSmokeTrail )
	{
		m_pSmokeTrail->StopEmission();
		m_pSmokeTrail = NULL;
	}

	EmitSound( "ASWGrenade.Incendiary" );
	DispatchParticleEffect( "vindicator_grenade", m_vecDetonateOrigin, vec3_angle );
}
