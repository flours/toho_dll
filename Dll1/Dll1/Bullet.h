#pragma once

typedef struct {
	//フラグ、種類、カウンタ、色、状態、少なくとも消さない時間、エフェクトの種類
	int flag, knd, cnt, col, state, till, eff;
	//座標、角度、速度、ベースの角度、一時記憶スピード
	double x, y, angle, spd, base_angle, rem_spd;
}bullet_t;

