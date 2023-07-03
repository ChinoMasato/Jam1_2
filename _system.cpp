#include "_system.h"
#include "DxLib.h"
#include <math.h>
#include "player.h"
#include "enemy.h"

int playerimg;//プレイヤー画像
int enemyimg;//敵画像
//int shot_normalimg;//弾画像
int shipimg;
int canon_1_leftimg;
int canon_1_rightimg;
int canon_2_leftimg;
int canon_2_rightimg;
int canon_3_left_upimg;
int canon_3_right_upimg;
int canon_3_left_downimg;
int canon_3_right_downimg;
int bossimg;

int count = 0;
int one_second = 60;
int time = 0;
int gameOverFlag = 0;
int score = 0;

SYSTEM sys[sys_];

void updateGame()
{
	count++;
	if (count % one_second == 0) //144で1秒？(学校のPCの場合)
	{
		time++;
	}
	if (pl.muteki_time > 0)
	{
		pl.muteki_time--;
	}
	if (enemy[57].enemytype == BOSS && enemy[57].enable == false && time > 35)
	{
		if (score <= 0)
		{
			score = 0;
		}
		DrawFormatString(350, 300, GetColor(255, 255, 0), "ゲームクリア！");
		DrawFormatString(350, 348, GetColor(255, 255, 0), "スコア %d", score);
	}
}

//円の当たり判定関数
bool isHit(entity en1, Object en2)
{
	//二つの円の当たり判定
	double dx = en1.x - en2.x;//横の距離
	double dy = en1.y - en2.y;//縦の距離
	double r2 = en1.r + en2.r;//半径の合算

	if (dx* dx + dy * dy < r2 * r2)
	{
		//当たっている
		return true;
	}
	return false;
}

//進行方向の右側にターゲットがいるか判定する関数
bool isRight(Object shot, entity target)
{
	double dy = target.y - shot.y;
	double dx = target.x - shot.x;
	double cross = shot.vx * dy - shot.vy * dx;

	return cross > 0;
}

//どういう関数かわからんが一応入れた
void RotVec(Object& shot, double r)
{
	double rot = r * (3.1415926539 / 180.0f);

	double rx = cos(rot) * shot.vx - sin(rot) * shot.vy;
	double ry = sin(rot) * shot.vx + cos(rot) * shot.vy;

	shot.vx = rx;
	shot.vy = ry;
}