function OnGameEvent_mission_success(params) {
	if (!g_bool_TraitorWin) {
		g_bool_IafWin = true;
	}
}

function OnGameEvent_mission_failed(params) {
	// 如果是技术图和技术死亡，IAF胜利
	if (g_bool_TechMap && g_bool_TechKill) // This will never happen 这个永远不会触发，不确定启用之后会不会不平衡
	{
		g_bool_IafWin = true;
		Director.MissionComplete(true);
		return;
	}

	// 如果内鬼存活数量大于0，内鬼胜利
	if (g_int_TraitorAliveCount > 0) {
		g_bool_TraitorWin = true;
		Director.MissionComplete(true);
		return;
	}

	// 否则说明没有胜利者，由于update()函数中有延迟，可能被快速重启跳过显示，所以只能在这里直接显示
	ShowSpeciallRolesList();
	LocalizedClientPrint(null, 3, g_str_TraitorNameList, "#challenge_traitors_traitor_list", "#challenge_traitors_traitor_player_unavailable");
	LocalizedClientPrint(null, 3, TextColor(128, 128, 105) + "%s1", "#challenge_traitors_no_winner");
	WriteMatchResultToFile(0);
	DestroyHudAndVGui();
}