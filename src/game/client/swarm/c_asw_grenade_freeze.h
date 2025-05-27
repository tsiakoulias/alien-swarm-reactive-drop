#ifndef _INCLUDED_C_ASW_GRENADE_FREEZE_H
#define _INCLUDED_C_ASW_GRENADE_FREEZE_H

#pragma once

#include "c_asw_grenade_cluster.h"

class C_ASW_Grenade_Freeze : public C_ASW_Grenade_Cluster
{
	DECLARE_CLASS( C_ASW_Grenade_Freeze, C_ASW_Grenade_Cluster );
	DECLARE_CLIENTCLASS();

public:
	virtual void Detonate();
	virtual void CreateSmokeTrail();
};

#endif	// _INCLUDED_C_ASW_GRENADE_FREEZE_H
