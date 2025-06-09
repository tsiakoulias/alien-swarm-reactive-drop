function OnGameEvent_weapon_fire(params) {
    return;
	local hWeapon = EntIndexToHScript(params["weapon"]);

	local fFireRate = 3.0;
    local fFireDuration = 1;
	EntFireByHandle(hWeapon, "RunScriptCode", "NetProps.SetPropFloat( self, \"m_flNextPrimaryAttack\", " + (Time() + fFireRate).tostring() + " );", 0.0, null, null);
    EntFireByHandle(hWeapon, "RunScriptCode", "NetProps.SetPropFloat( self, \"m_flDelayedFire\", " + (fFireDuration).tostring() + " );", 0.0, null, null);
    //m_fFireDuration
}