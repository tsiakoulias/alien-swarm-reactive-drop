/*参数说明
	float   0  - 起始时间
	float   1  - 结束时间
	float   2  - 初始强度
	float	3  - 当前强度

	entity 0 - marine
*/

function Paint() {
	// if we are not playing or not spectating this marine, dont show
	if (self.GetEntity(0) != GetLocalPlayer().GetViewNPC()) {
		return;
	}
	local time = Time();
	local start = self.GetFloat(0);
	local end = self.GetFloat(1);
	if (time < start || time > end) {
		return;
	}


	self.PaintRectangle(0, 0, ScreenWidth(), ScreenHeight(), 255, 255, 255, Alpha(time, start, end));
}

function Alpha(time, start, end) {
	local ratio = (time - start) / (end - start);
	local currentIntensity = self.GetFloat(2) * (1 - ratio * ratio);
	return 200 * currentIntensity;
}