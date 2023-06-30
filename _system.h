#pragma once
//struct と enum の記入場所
enum EnemyType
{
	ENEMY1,//敵タイプ１
	ENEMY2,//敵タイプ２
	ENEMY3//敵タイプ3
};

enum ShotType
{
	NORMAL,
	BOMB,
	BEAM
};

//円の構造体
struct Object
{
	EnemyType type;//敵の種類
	ShotType type;
	double x;//X座標
	double y;//Y座標
	double r;//半径
	int color;//円の色
	bool fill;//塗りつぶすか否か
	double vx;//横の移動量
	double vy;//縦の移動量
	double vvx;//横の移動量の増量
	double vvy;//縦の移動量の増量
	bool enable;//有効フラグ（生きてるか、死んでるか）
	int cooltime;//連射できないようにするタイマー
	double rad = 0;
	int hp;
	int muteki_time = 0;
	int aim_time = 0;
	int action;
};