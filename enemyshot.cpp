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

Object enemyshot[EnemyShotNum];//íe
//íeÇÃèâä˙âª
void initEnemyShot()
{
	for (int i = 0; i < EnemyShotNum; i++) {
		enemyshot[i].r = 5;
		enemyshot[i].color = GetColor(255,255, 0);
		enemyshot[i].fill = true;
		enemyshot[i].enable = false;
	}
}
//íeÇÃçXêV
void updateEnemyShot()
{
	//íeÇ™óLå¯Ç»Ç∆Ç´Ç…íeÇìÆÇ©Ç∑
	for (int i = 0; i < EnemyShotNum; i++)
	{
		if (enemyshot[i].enable == true) {
			//íeÇÃéÌóﬁÇ…âûÇ∂ÇƒìÆÇ´ï˚ÇïœÇ¶ÇÈ
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
				//ìñÇΩÇ¡ÇƒÇ¢ÇÈ
				if (enemyshot[i].enable == true && pl.muteki_time <= 0)
				{
					gameOverFlag++;
					pl.muteki_time = one_second * 1; //3ïbä‘ñ≥ìGéûä‘Ç™Ç≈Ç´ÇÈ
				}
			}
		}
	}
}
//íeÇÃï`âÊ
void drawEnemyShot()
{
	for (int i = 0; i < EnemyShotNum; i++) {
		if (enemyshot[i].enable == true)
		{
			if (enemyshot[i].enemyshottype == NORMAL)
			{
				//ìGíe(í èÌ)ÇÃâÊëú
				
				DrawCircle(enemyshot[i].x, enemyshot[i].y, enemyshot[i].r, enemyshot[i].color, enemyshot[i].fill);
			}
			if (enemyshot[i].enemyshottype == BOMB_MOVE)
			{
				//enemyshot[i].color = GetColor(255, 255, 0);
				//ìGíe(É{ÉÄ)ÇÃâÊëú
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
				//ìGíe(ÉrÅ[ÉÄ)ÇÃâÊëú
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
			//ÉrÅ[ÉÄÇèoÇµêÿÇÈÇ‹Ç≈ÉJÉEÉìÉgÉ_ÉEÉìÇ∑ÇÈ
			if (enemyshot[i].launchtime_B > 0)
			{
				enemyshot[i].launchtime_B--;
			}
		}
	}
}