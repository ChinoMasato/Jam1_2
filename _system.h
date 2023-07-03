#pragma once
//struct と enum の記入場所

extern int playerimg;//プレイヤー画像
//extern int shot_normalimg;//弾画像

extern int enemyimg;//敵画像
extern int shipimg;//戦艦画像
extern int canon_1_leftimg;
extern int canon_1_rightimg;
extern int canon_2_leftimg;
extern int canon_2_rightimg;
extern int canon_3_left_upimg;
extern int canon_3_right_upimg;
extern int canon_3_left_downimg;
extern int canon_3_right_downimg;
extern int bossimg;

enum EnemyType
{
	ENEMY1,//真っ直ぐ動いて、真っ直ぐ弾を撃つ
	ENEMY2,//隊列で出現して、波線を描きながら突進してくる
	ENEMY3,//不規則に動いて、ホーミング弾を撃つ
	ENEMY4,//円形に弾を撃つ
	SHIP,//戦艦
	CANON1,//大砲1
	CANON2,//大砲2
	CANON3,//大砲3
	BOSS//ボス
};

enum ShotType
{
	NORMAL,
	BOMB_MOVE,
	BOMB_EXPLOSION,
	BEAM_STANDBY,
	BEAM_LAUNCH
};

enum Place
{
	LEFT_UP,
	LEFT_DOWN,
	RIGHT_UP,
	RIGHT_DOWN
};

//円の構造体
struct Object
{
	EnemyType enemytype;//敵の種類
	ShotType enemyshottype;
	Place place;//砲台の位置
	ShotType shottype;
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
	int bomb_x;
	int bomb_y;
	int boss_cooltime_M;
	int boss_cooltime_S;
	int boss_cooltime_B;
	int standbytime_B;
	int launchtime_B;
};


/*-----------------------------------------------------------------------------------------------*/


enum SCENE
{
	scene1, scene2, scene3, scene4
};

enum PLshot
{
	type1, type2, type3
};

struct entity
{
	double x, y, r;
	double x1, x2, x3, x4, y1, y2, y3, y4;
	double vx, vy, vvx, vvy;

	int color;
	bool live;
	int time;
	int muteki_time;
	int hp;
};

struct SYSTEM
{
	int se_shot;
	int se_break;
	int se_clear;
	int count_skin;
	int count_scene;
};

const int sys_ = 10;

extern SCENE scene;
extern PLshot pl_shot_type;
extern SYSTEM sys[sys_];


/*----------------------------------------------------------------------------------------------*/


bool isHit(entity en1, Object en2);//当たり判定関数
bool isRight(Object shot, entity target);//進行方向の右にいるか

//どういう関数かわからんが一応入れた
void RotVec(Object& shot, double r);

void updateGame();


void scene_1();
void scene_2();
void scene_3();
void scene_4();