#include "_system.h"
#include <math.h>

int playerimg;//プレイヤー画像
int enemyimg;//敵画像
int shot_normalimg;//弾画像

//円の当たり判定関数
bool isHit(Object en1, Object en2)
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
bool isRight(Object shot, Object target)
{
	double dy = target.y - shot.y;
	double dx = target.x - shot.x;
	double cross = shot.vx * dy - shot.vy * dx;

	return cross > 0;
}
void RotVec(Object& shot, double r)
{
	double rot = r * (3.1415926539 / 180.0f);

	double rx = cos(rot) * shot.vx - sin(rot) * shot.vy;
	double ry = sin(rot) * shot.vx + cos(rot) * shot.vy;

	shot.vx = rx;
	shot.vy = ry;
}