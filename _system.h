#pragma once
//struct と enum の記入場所

extern int playerimg;//プレイヤー画像
extern int enemyimg;//敵画像
extern int shot_normalimg;//弾画像

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
	int cooltime_B;//連射できないようにするタイマー(ボムver)
	double rad = 0;
	int hp;
	int muteki_time = 0;//プレイヤーの無敵時間
	int aim_time = 0;//ホーミングする時間(ずっとホーミングさせない)
	int action;//敵の行動パターンなどに
	int bombtime;//ボムの爆発が終わるまでの時間(1秒を想定)
};

bool isHit(Object en1, Object en2);//当たり判定関数
bool isRight(Object shot, Object target);//進行方向の右にいるか

//どういう関数かわからんが一応入れた
void RotVec(Object& shot, double r);