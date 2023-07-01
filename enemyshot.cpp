#include "_system.h"
#include "DxLib.h"
#include "enemyshot.h"
#include "player.h"
//#include "game.h"
#include <math.h>

extern int start;
extern bool gameOverFlag;
extern int stage;
extern double d;
extern double dx;
extern double dy;
extern double speed;
extern int one_second;
extern int count;

Object enemyshot[EnemyShotNum];//’e
//’e‚Ì‰Šú‰»
void initEnemyShot()
{
	for (int i = 0; i < EnemyShotNum; i++) {
		enemyshot[i].r = 5;
		enemyshot[i].color = GetColor(0,255, 0);
		enemyshot[i].fill = true;
		enemyshot[i].enable = false;
	}
}
//’e‚ÌXV
void updateEnemyShot()
{
	if (start == 0)
	{
		//’e‚ª—LŒø‚È‚Æ‚«‚É’e‚ğ“®‚©‚·
		for (int i = 0; i < EnemyShotNum; i++)
		{
			if (enemyshot[i].enable == true) {
				//’e‚Ìí—Ş‚É‰‚¶‚Ä“®‚«•û‚ğ•Ï‚¦‚é
				if (enemyshot[i].enemytype == ENEMY1) {
					enemyshot[i].vx = enemyshot[i].vx + enemyshot[i].vvx;
					enemyshot[i].vy = enemyshot[i].vy + enemyshot[i].vvy;
				}
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
			if (isHit(player, enemyshot[i]))
			{
				//“–‚½‚Á‚Ä‚¢‚é
				if (player.muteki_time <= 0)
				{
					if (player.hp > 0)
					{
						player.hp--;
						PlaySoundFile("STG_player_damege.mp3", DX_PLAYTYPE_BACK);

						//ƒfƒoƒbƒO—p
						//player.hp++;
						if (player.hp <= 0)
						{
							player.color = enemyshot[i].color;
							if (gameOverFlag == false)
							{
								StopMusic();
								PlayMusic("STG_gameover.mp3", DX_PLAYTYPE_LOOP);
								PlaySoundFile("STG_enemy_defeat.mp3", DX_PLAYTYPE_BACK);
							}
							gameOverFlag = true;//ƒQ[ƒ€ƒI[ƒo[ƒtƒ‰ƒO‚ğ—§‚Ä‚é
						}
						else {
							player.muteki_time = one_second * 3; //3•bŠÔ–³“GŠÔ‚ª‚Å‚«‚é
						}
					}
				}
			}
		}
	}
}
//’e‚Ì•`‰æ
void drawEnemyShot()
{
	for (int i = 0; i < EnemyShotNum; i++) {
		if (enemyshot[i].enable == true && start == 0)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127); //”¼“§–¾
			DrawCircle(enemyshot[i].x, enemyshot[i].y, enemyshot[i].r, enemyshot[i].color, enemyshot[i].fill);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //•s“§–¾
			DrawCircle(enemyshot[i].x, enemyshot[i].y, enemyshot[i].r / 2, enemyshot[i].color, enemyshot[i].fill);
		}
	}
}