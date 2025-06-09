// 计算从起点到终点的抛射初速度向量
// 参数：
//   src: 起点坐标 (Vector)
//   dest: 终点坐标 (Vector)
//   gravity: 重力加速度（向下为正，单位：units/s²）
//   flightTime: 飞行时间（若为0则自动计算）
// 返回：初速度向量 (Vector)
function LaunchVector(src, dest, gravity, flightTime = 0.0) {
	// 1. 计算水平方向向量和距离
	local delta = dest - src;
	local horizontalDelta = Vector(delta.x, delta.y, 0); // 水平方向位移
	local horizontalDistance = horizontalDelta.Norm(); // 水平距离，同时将向量标准化

	// 2. 若未指定飞行时间，则根据水平距离和重力计算默认值
	if (flightTime <= 0) {
		// 最小飞行时间限制为0.8秒，避免速度过大
		flightTime = max(0.8, sqrt((horizontalDistance * 1.5) / gravity));
	}

	// 3. 计算垂直初速度 velocity_z（考虑重力加速度和高度差）
	local deltaHeight = dest.z - src.z; // 垂直高度差
	local velocity_z = (deltaHeight / flightTime) + (0.5 * gravity * flightTime);

	// 4. 计算水平初速度 velocity_horizontal
	local horizontalDirection = (horizontalDistance > 0) ? horizontalDelta : Vector(0, 0, 0);
	local velocity_horizontal = horizontalDirection * (horizontalDistance / flightTime);

	// 5. 组合速度向量
	return Vector(velocity_horizontal.x, velocity_horizontal.y, velocity_z);
}
// 使用偏移数组和循环生成信标
g_arr_BeaconOffsets <- [
	Vector(-125, -125, 70),
	Vector(-125, 125, 70),
	Vector(125, -125, 70),
	Vector(125, 125, 70)
];

function OnGameEvent_heal_beacon_placed(params) {
	local hHealBeacon = EntIndexToHScript(params["entindex"]);
	local hMarine = EntIndexToHScript(params["marine"]);
	local targetPos = NetProps.GetPropVector(hMarine.GetCommander(), "m_vecCrosshairTracePos");
	local HealBeaconOrigin = hHealBeacon.GetOrigin();
	hHealBeacon.Destroy();

	local hNewHealBeacon;
	local hNewDamageAmplifier;
	local hNewFreezeGrenade;
	foreach(offset in g_arr_BeaconOffsets) {
		hNewHealBeacon = PlaceHealBeacon(230, 6, 3.65, 23, 180, HealBeaconOrigin + offset);
		hNewHealBeacon.SetVelocity(LaunchVector(hNewHealBeacon.GetOrigin(), targetPos, 150, 0.5));

		if (RandIntUniformDistribution(0, 999) >= 945) {
			hNewDamageAmplifier = PlaceDamageAmplifier(30, 180, HealBeaconOrigin + offset);
			hNewDamageAmplifier.SetVelocity(LaunchVector(hNewDamageAmplifier.GetOrigin(), targetPos, 150, 0.5));
		}

		if (RandIntUniformDistribution(0, 999) >= 669) {
			hNewFreezeGrenade = DropFreezeGrenade(30, 2, 180, HealBeaconOrigin + offset);
			hNewFreezeGrenade.SetVelocity(LaunchVector(hNewFreezeGrenade.GetOrigin(), targetPos, 150, 0.5));
		}
	}
	return;
}