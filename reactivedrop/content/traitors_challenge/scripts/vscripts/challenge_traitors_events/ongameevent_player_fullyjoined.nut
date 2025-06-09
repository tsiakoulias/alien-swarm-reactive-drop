g_ModeScript.OnGameEvent_player_fullyjoined <-  function(params) {
	local hPlayer = GetPlayerFromUserID(params["userid"]);
	if (hPlayer != null) {
		CreatePlayerHud(hPlayer);
	}
}