#pragma once
//円の構造体
struct En
{
	double x;//X座標
	double y;//Y座標
	double r;//半径
	int color;//円の色
	bool fill;//塗りつぶすか否か
	double vx;//横の移動量
	double vy;//縦の移動量
	bool enable;//有効フラグ（生きてるか、死んでるか）
	int cooltime;//連射できないようにするタイマー
};

bool isHit(En en1, En en2);//当たり判定関数
