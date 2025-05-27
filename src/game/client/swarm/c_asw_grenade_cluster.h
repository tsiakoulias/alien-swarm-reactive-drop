#ifndef _INCLUDED_C_ASW_GRENADE_CLUSTER_H
#define _INCLUDED_C_ASW_GRENADE_CLUSTER_H

#pragma once

#include "c_asw_grenade_vindicator.h"

class C_ASW_Grenade_Cluster : public C_ASW_Grenade_Vindicator
{
	DECLARE_CLASS( C_ASW_Grenade_Cluster, C_ASW_Grenade_Vindicator );
	DECLARE_CLIENTCLASS();

public:
	virtual void Detonate();
};

#endif	// _INCLUDED_C_ASW_GRENADE_CLUSTER_H
