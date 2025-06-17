g_str_sound <- "Traitors.Flashbang";
g_arr_TraceOffset <- [];
for (local i = -8; i <= 8; i += 4) {
	for (local j = -8; j <= 8; j += 4) {
		for (local k = -8; k <= 8; k += 4) {
			g_arr_TraceOffset.append(Vector(i, j, k));
		}
	}
}

function OnGameEvent_flare_placed(params) {
	g_tbl_Flashbang[params["entindex"]] <- ((g_int_Counter + 10) / 5) * 5;
	EntIndexToHScript(params["entindex"]).PrecacheSoundScript(g_str_sound);
}

g_tbl_TraceTable <- {
	start = Vector(0, 0, 0)
	end = Vector(0, 0, 0)
	mask = ENGINE_CONTENTS.CONTENTS_SOLID | ENGINE_CONTENTS.CONTENTS_MOVEABLE | ENGINE_CONTENTS.CONTENTS_DEBRIS
};

function GetHitCount(startOrigin, marineOrigin) {
	local hitCount = 0;
	g_tbl_TraceTable.start = startOrigin;
	foreach(traceOffset in g_arr_TraceOffset) {
		g_tbl_TraceTable.end = marineOrigin + traceOffset;
		TraceLineTable(g_tbl_TraceTable);
		if (g_tbl_TraceTable.hit) {
			hitCount++;
		}
	}
	return hitCount;
}

function Flashbang(interval) {
	if (g_int_Counter % interval != 0) {
		return;
	}
	local flare = null;
	local flareOrigin;
	local marineOrigin;
	local vecFlare;
	local vecFacing;
	local cosTheta;
	local distance;
	local hPlayer = null;
	local hHud = null;
	local hitcount;
	local exposureRatio;

	foreach(idx, time in g_tbl_Flashbang) {
		if (time != g_int_Counter) {
			continue;
		}
		flare = EntIndexToHScript(idx);
		if (flare == null || !flare.IsValid()) {
			delete g_tbl_Flashbang[idx];
			continue;
		}

		flareOrigin = flare.GetOrigin();
		g_tbl_TraceTable.start = flareOrigin;
		foreach(hMarine in g_marine_Total) {
			if (hMarine == null || !hMarine.IsValid()) {
				continue;
			}
			hitcount = 0;
			marineOrigin = hMarine.GetOrigin() + Vector(0, 0, 80);
			FadeClientVolume(hMarine.GetCommander(), 0.5, 5, 50, 5);
			EntIndexToHScript(idx).EmitSound(g_str_sound);
			hitcount = GetHitCount(flareOrigin, marineOrigin);
			exposureRatio = 1.0 - hitcount / 125.0;
			vecFlare = flareOrigin - marineOrigin;
			distance = vecFlare.Norm();
			if (hMarine.IsInhabited()) {
				vecFacing = hMarine.GetCommander().GetCrosshairTracePos() - marineOrigin;
			} else {
				vecFacing = EulerToVectors(hMarine.GetAngles());
			}
			vecFacing.Norm();
			cosTheta = vecFacing.Dot(vecFlare);
			local intensity = 0;
			if (cosTheta > 0) {
				if (distance > 300) {
					intensity = cosTheta / distance / distance * 90000.0;
				} else {
					intensity = cosTheta * (1.0 + 0.25 * (1 - (distance / 300.0) * (distance / 300.0)));
				}
			} else {
				continue;
			}
			local hHud = Entities.FindByName(null, hMarine.GetScriptScope().strFlashbangHudName);
			local ratio = (Time() - hHud.GetFloat(0)) / (hHud.GetFloat(1) - hHud.GetFloat(0));
			if (Time() >= hHud.GetFloat(1)) {
				ratio = 1.0;
			}
			local currentIntensity = hHud.GetFloat(2) * (1 - ratio * ratio);
			local newIntensity = sqrt(pow(currentIntensity, 2.0) + pow(intensity * exposureRatio, 2.0));
			hHud.SetFloat(0, Time());
			hHud.SetFloat(1, Time() + 3 + 5 * exposureRatio);
			hHud.SetFloat(2, newIntensity > 1.25 ? 1.25 : newIntensity);
		}
		flare.Destroy();
	}
}

function EulerToVectors(vec) {
	local PI = 3.14159;
	// 角度转换为弧度
	local radPitch = vec.x * PI / 180.0;
	local radYaw = vec.y * PI / 180.0;

	// 计算三角函数值
	local cosPitch = cos(radPitch);
	local sinPitch = sin(radPitch);
	local cosYaw = cos(radYaw);
	local sinYaw = sin(radYaw);

	local res = Vector(0, 0, 0);
	// 计算前向向量（Forward Vector）
	res.x = cosPitch * cosYaw,
		res.y = cosPitch * sinYaw,
		res.z = -sinPitch

	return res;
}