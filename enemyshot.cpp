#include "_system.h"
#include "DxLib.h"
#include "enemyshot.h"
#include "player.h"
//#include "game.h"
#include <math.h>

extern int start;
extern int gameOverFlag;
extern int stage;
extern double d;
extern double dx;
extern double dy;
extern double speed;
extern int one_second;
extern int count;
extern bool gameClearFlag;

Object enemyshot[EnemyShotNum];//弾
//弾の初期化
void initEnemyShot()
{
	for (int i = 0; i < EnemyShotNum; i++) {
		enemyshot[i].r = 5;
		enemyshot[i].color = GetColor(255,255, 0);
		enemyshot[i].fill = true;
		enemyshot[i].enable = false;
	}
}
//弾の更新
void updateEnemyShot()
{
	//弾が有効なときに弾を動かす
	for (int i = 0; i < EnemyShotNum; i++)
	{
		if (enemyshot[i].enable == true) {
			//弾の種類に応じて動き方を変える
			if (enemyshot[i].enemytype == ENEMY1 || enemyshot[i].enemytype == ENEMY4) {
			}
			if (enemyshot[i].enemytype == ENEMY3 && enemyshot[i].aim_time > 0) {
				if (isRight(enemyshot[i], pl))
				{
					RotVec(enemyshot[i], 1);
				}
				else {
					RotVec(enemyshot[i], -1);
				}
				enemyshot[i].aim_time--;
			}
			if ((enemyshot[i].enemytype == CANON1 || enemyshot[i].enemytype == BOSS) && enemyshot[i].aim_time > 0)
			{
				if (isRight(enemyshot[i], pl))
				{
					RotVec(enemyshot[i], 1);
				}
				else {
					RotVec(enemyshot[i], -1);
				}
				enemyshot[i].aim_time--;
			}
			enemyshot[i].vx = enemyshot[i].vx + enemyshot[i].vvx;
			enemyshot[i].vy = enemyshot[i].vy + enemyshot[i].vvy;
			enemyshot[i].x = enemyshot[i].x + enemyshot[i].vx;
			enemyshot[i].y = enemyshot[i].y + enemyshot[i].vy;
			if (enemyshot[i].x >= 800 ||
				enemyshot[i].x < 0 ||
				enemyshot[i].y >= 600 ||
				enemyshot[i].y < 0)
			{
				enemyshot[i].enable = false;
			}
		}
		if (gameClearFlag == false)
		{
			if (isHit(pl, enemyshot[i]))
			{
				//当たっている
				if (enemyshot[i].enable == true && pl.muteki_time <= 0)
				{
					gameOverFlag++;
					pl.muteki_time = one_second * 1; //3秒間無敵時間ができる
				}
			}
		}
	}
}
//弾の描画
void drawEnemyShot()
{
	for (int i = 0; i < EnemyShotNum; i++) {
		if (enemyshot[i].enable == true)
		{
			if (enemyshot[i].enemyshottype == NORMAL)
			{
				//敵弾(通常)の画像
				
				DrawCircle(enemyshot[i].x, enemyshot[i].y, enemyshot[i].r, enemyshot[i].color, enemyshot[i].fill);
			}
			if (enemyshot[i].enemyshottype == BOMB_MOVE)
			{
				//enemyshot[i].color = GetColor(255, 255, 0);
				//敵弾(ボム)の画像
				if (enemyshot[i].bombtime > 0 && isHit( pl,enemyshot[i]) == false)
				{
					enemyshot[i].r = 5;
					DrawCircle(enemyshot[i].x, enemyshot[i].y, enemyshot[i].r, enemyshot[i].color, enemyshot[i].fill);
				}
				if (enemyshot[i].bombtime <= 0 || isHit(pl,enemyshot[i]) == true)
				{
					enemyshot[i].enemyshottype = BOMB_EXPLOSION;
					enemyshot[i].bomb_x = enemyshot[i].x;
					enemyshot[i].bomb_y = enemyshot[i].y;
					enemyshot[i].r = 5;
				}
			}
			if (enemyshot[i].enemyshottype == BOMB_EXPLOSION)
			{
				DrawCircle(enemyshot[i].bomb_x, enemyshot[i].bomb_y, enemyshot[i].r, enemyshot[i].color, enemyshot[i].fill);
				enemyshot[i].r += 25;
				if (enemyshot[i].r >= 75)
				{
					enemyshot[i].r = 5;
					enemyshot[i].enable = false;
				}
			}
			if (enemyshot[i].enemyshottype == BEAM_STANDBY)
			{
				//敵弾(ビーム)の画像
				if (enemyshot[i].standbytime_B > 0)
				{
					enemyshot[i].r = 5;
					if (enemyshot[i].y < 610)
					{
						DrawCircle(enemyshot[i].x, enemyshot[i].y, enemyshot[i].r, enemyshot[i].color, enemyshot[i].fill);
						enemyshot[i].y += 5;
					}
				}
				if (enemyshot[i].standbytime_B <= 0)
				{
					enemyshot[i].enemyshottype = BEAM_LAUNCH;
					enemyshot[i].r = 5;
				}
			}
			if (enemyshot[i].enemyshottype == BEAM_LAUNCH)
			{
				enemyshot[i].r = 75;
				if (enemyshot[i].launchtime_B > 0)
				{
					DrawCircle(enemyshot[i].x, enemyshot[i].y, enemyshot[i].r, enemyshot[i].color, enemyshot[i].fill);
					if (enemyshot[i].y < 700)
					{
						enemyshot[i].y += 75;
					}
				}
			}
			//ビームを出し切るまでカウントダウンする
			if (enemyshot[i].launchtime_B > 0)
			{
				enemyshot[i].launchtime_B--;
			}
		}
	}
}