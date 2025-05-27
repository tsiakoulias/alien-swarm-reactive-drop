g_arr_pattern <- [
	"%article%",
	"%role%",
	"%team%",
	"%team_objective_long%",
	"%team_objective_short%",
	"%chat_skill_instruction%",
	"%hud_skill_instruction%",
];

function GetLocalizedString(key, language, role = ROLE.NONE) {
	if (key == null) {
		return "";
	}
	local temp = key.slice(1, key.len());
	local tempstr = "";
	if (g_localizations.rawin(language) && g_localizations[language].rawin(temp)) {
		tempstr = g_localizations[language][temp];
	} else {
		tempstr = "[" + language + "]" + key + " does not exist.";
	}
	if (role == ROLE.NONE) {
		return tempstr;
	}
	local strRole = GetRoleString(role);
	local strTeam = "";
	if (role >= 0 && role <= ROLE.MAX_IAF_TEAM) {
		strTeam = "iaf";
	} else if (role >= ROLE.MAX_IAF_TEAM && role <= ROLE.MAX_TRAITOR_TEAM) {
		strTeam = "traitor";
	}
	local flg = true;
	while (flg) {
		flg = false;
		foreach(i, pattern in g_arr_pattern) {
			local begin = null;
			if ((begin = tempstr.find(pattern)) != null) {
				flg = true;
				local end = begin + pattern.len();
				switch (i) {
					case 0:
						tempstr = tempstr.slice(0, begin) + GetLocalizedString("#challenge_traitors_role_article_" + strRole, language, role) + tempstr.slice(end);
						break;
					case 1:
						local tempstr2 = (role >= ROLE.INFECTED_OFFSET && role < ROLE.MAX_TRAITOR_TEAM) ? GetLocalizedString("#challenge_traitors_role_abeted", language, role) : "";
						tempstr = tempstr.slice(0, begin) + GetLocalizedString("#challenge_traitors_role_name_" + strRole, language, role) + tempstr2 + tempstr.slice(end);
						break;
					case 2:
						tempstr = tempstr.slice(0, begin) + GetLocalizedString("#challenge_traitors_team_name_" + strTeam, language) + tempstr.slice(end);
						break;
					case 3:
						tempstr = tempstr.slice(0, begin) + GetLocalizedString("#challenge_traitors_team_objective_long_" + strTeam, language) + tempstr.slice(end);
						break;
					case 4:
						tempstr = tempstr.slice(0, begin) + GetLocalizedString("#challenge_traitors_team_objective_short_" + strTeam, language) + tempstr.slice(end);
						break;
					case 5:
						tempstr = tempstr.slice(0, begin) + GetLocalizedString("#challenge_traitors_chat_skill_instruction", language) + tempstr.slice(end);
						break;
					case 6:
						tempstr = tempstr.slice(0, begin) + GetLocalizedString("#challenge_traitors_hud_skill_instruction", language) + tempstr.slice(end);
						break;
				}
			}
		}
	}

	return tempstr;
}

function LocalizedClientPrint(client, index, str, param1 = null, param2 = null, param3 = null, param4 = null, role = ROLE.NONE) {
	if (client == null) {
		local hPlayer = null;
		while ((hPlayer = Entities.FindByClassname(hPlayer, "player")) != null) {
			local strLanguage = GetClientLanguage(hPlayer.entindex());
			ClientPrint(hPlayer, index, str, GetLocalizedString(param1, strLanguage, role), GetLocalizedString(param2, strLanguage, role), GetLocalizedString(param3, strLanguage, role), GetLocalizedString(param4, strLanguage, role));
		}
	} else {
		local strLanguage = "english";
		try {
			strLanguage = GetClientLanguage(client.entindex());
		} catch (exception) {
			printl("LocalizedClientPrint() Line 153:\t" + client.IsValid());
		}
		ClientPrint(client, index, str, GetLocalizedString(param1, strLanguage, role), GetLocalizedString(param2, strLanguage, role), GetLocalizedString(param3, strLanguage, role), GetLocalizedString(param4, strLanguage, role));
	}
}

function GetClientLanguage(playerIndex) {
	local language = "english";
	try {
		language = Convars.GetClientConvarValue(playerIndex, "cl_language");
	} catch (e) {}
	return language;
}

function GetRoleString(role) {
	local strRole = "";
	switch (role) {
		case ROLE.NONE:
			strRole = "NONE";
			break;
		case ROLE.IAF:
			strRole = "IAF";
			break;
		case ROLE.SCANNER:
			strRole = "SCANNER";
			break;
		case ROLE.BIOCHEMIST:
			strRole = "BIOCHEMIST";
			break;
		case ROLE.IAF_LEADER:
			strRole = "IAF_LEADER";
			break;
		case ROLE.SHIELD:
			strRole = "SHIELD";
			break;
		case ROLE.SNIPER:
			strRole = "SNIPER";
			break;
		case ROLE.DEMO:
			strRole = "DEMO";
			break;
		case ROLE.DESERTER:
			strRole = "DESERTER";
			break;
		case ROLE.TRAITOR:
			strRole = "TRAITOR";
			break;
		case ROLE.TRAITOR_LEADER:
			strRole = "TRAITOR_LEADER";
			break;
		case ROLE.INFECTOR:
			strRole = "INFECTOR";
			break;
		case ROLE.BOOMER:
			strRole = "BOOMER";
			break;
		case ROLE.SILENCER:
			strRole = "SILENCER";
			break;
		case ROLE.MIMIC:
			strRole = "MIMIC";
			break;
		case ROLE.INFECTED_IAF:
			strRole = "IAF";
			break;
		case ROLE.INFECTED_SCANNER:
			strRole = "SCANNER";
			break;
		case ROLE.INFECTED_BIOCHEMIST:
			strRole = "BIOCHEMIST";
			break;
		case ROLE.INFECTED_IAF_LEADER:
			strRole = "IAF_LEADER";
			break;
		case ROLE.INFECTED_SHIELD:
			strRole = "SHIELD";
			break;
		case ROLE.INFECTED_SNIPER:
			strRole = "SNIPER";
			break;
		case ROLE.INFECTED_DEMO:
			strRole = "DEMO";
			break;
		case ROLE.INFECTED_DESERTER:
			strRole = "DESERTER";
			break;
		case ROLE.SPECTATOR:
			strRole = "SPECTATOR";
			break;
		default:
			printl("Undefined role string, in GetRoleString(role), in challenge_traitors_localize.nut");
	};
	strRole = strRole.tolower();
	return strRole;
}