#include "_system.h"
#include "DxLib.h"
#include <math.h>
#include "shot.h"
#include "enemyshot.h"
#include "enemy.h"
#include "player.h"
//#include "game.h"
//#include "effect.h"

extern bool gameOverFlag;//ゲームオーバー判定
extern int stage;
extern int i;
extern double speed;
extern double dx;
extern double dy;
extern double d;
extern int boss_defeat_num;
extern int start;
extern const int enemy_num;
extern int zenmetu;
extern int count;
extern int q;
extern int score;
extern int result;
extern int boss_action;
extern int j;
extern int action;
extern int one_second;

Object enemy[enemy_num];//敵
//敵の初期化
void initEnemy()
{
	//敵画像の読み込み
	enemyimg = LoadGraph("enemy_1_1.png");
	//敵の初期化処理
	for (i = 0; i < 10; i++) {
		enemy[i].x = GetRand(799);
		enemy[i].y = 0 - i * 100;
		enemy[i].r = 20;
		enemy[i].color = GetColor(255, 0, 0);
		enemy[i].fill = true;
		enemy[i].vx = 0.0;//xの移動量
		enemy[i].vy = 2.0;//yの移動量
		enemy[i].enable = true;

		enemy[i].hp = 1;
		enemy[i].enemytype = ENEMY1;
	}
	for (i = 10; i < 30; i++) {
		//double speed = 3.0;
		enemy[i].y = -1000 - i * 30;
		enemy[i].x = 200  * cos(enemy[i].y);
		enemy[i].r = 15;
		enemy[i].color = GetColor(255, 0, 0);
		enemy[i].fill = true;
		enemy[i].vx = 3.0;//xの移動量
		enemy[i].vy = 3.0;//yの移動量
		enemy[i].enable = true;

		enemy[i].hp = 1;
		enemy[i].enemytype = ENEMY2;
	}
}

//真っすぐ弾を撃つ
void straightShot(int rad, Object ene)
{
	//弾が無効なときのみ初期値をセットし有効にする
	for (int j = 0; j < EnemyShotNum; j++)
	{
		//撃てる弾をみつける
		if (enemyshot[j].enable == false) {
			//弾を撃つ
			enemyshot[j].x = ene.x;
			enemyshot[j].y = ene.y;
			double PI = 3.14159265358979323846264338;
			double minrad = PI / 180.0;//1度のラジアン
			double speed = 1.0;//速度
			enemyshot[j].vx = speed * cos(minrad * rad);
			enemyshot[j].vy = speed * sin(minrad * rad);
			enemyshot[j].enable = true;
			enemyshot[j].enemytype = ene.enemytype;
			enemyshot[j].vvx = enemyshot[j].vx * 0.01;
			enemyshot[j].vvy = enemyshot[j].vy * 0.01;
			break;
		}
	}
}

//爆発発生関数
//void explosion(Object ene)
//{
//	for (i = 0; i < EffectNum; i++)
//	{
//		if (effe[i].enable == false)
//		{
//			effe[i].enable = true;
//			effe[i].x = ene.x - 60;
//			effe[i].y = ene.y - 60;
//			effe[i].animeNo = 0;
//			break;
//		}
//	}
//}

//敵の更新
void updateEnemy()
{
	for (int i = 0; i < enemy_num; i++) {
		if (enemy[i].enable == true) {
			//敵を自動で動かす
			if (enemy[i].enemytype == ENEMY2)
			{
				enemy[i].vx = cos(enemy[i].vy);
			}
			enemy[i].x += enemy[i].vx;
			enemy[i].y += enemy[i].vy;
			if (enemy[i].x < 0 || enemy[i].x >= 800) {
				//もし左端・右端に出たら
				enemy[i].vx = enemy[i].vx * -1;
			}

			//弾を発射する
			if (canEnemyShot(enemy[i]))
			{
				if (enemy[i].enemytype == ENEMY1) {
					straightShot(180, enemy[i]);
					enemy[i].cooltime = one_second * 2;//連射速度　小さいほど連射できる
				}
			}

			if (isHit(player, enemy[i]))
			{
				//当たっている
				if (player.muteki_time <= 0)
				{
					if (player.hp > 0)
					{
						player.hp--;
						PlaySoundFile("STG_player_damege.mp3", DX_PLAYTYPE_BACK);

						//デバッグ用
						//player.hp++;
						if (player.hp <= 0)
						{
							player.color = enemyshot[i].color;
							if (gameOverFlag == false)
							{
								StopMusic();
								PlayMusic("STG_gameover.mp3", DX_PLAYTYPE_LOOP);
								PlaySoundFile("STG_enemy_defeat.mp3", DX_PLAYTYPE_BACK);
								explosion(enemy[i]);//爆発
							}
							gameOverFlag = true;//ゲームオーバーフラグを立てる
						}
						else {
							player.muteki_time = one_second * 3; //60毎フレーム*3=180→3秒間無敵時間ができる
						}
					}
				}
			}

			for (int j = 0; j < ShotNum; j++) {
				//敵と弾との当たり判定
				if (shot[j].enable == true) {
					if (isHit(shot[j], enemy[i]))
					{
						//当たっている
						if (enemy[i].hp > 0)
						{
							enemy[i].hp--;
						}
						if (enemy[i].hp <= 0)
						{
							if (enemy[i].enable == true)
							{
								PlaySoundFile("STG_enemy_defeat.mp3", DX_PLAYTYPE_BACK);
								explosion(enemy[i]);//爆発
							}
							enemy[i].enable = false;//敵を無効
						}
						shot[j].enable = false;//弾を無効
						break;
					}
				}
			}
			//銃を冷やす処理
			if (enemy[i].cooltime > 0) {
				enemy[i].cooltime--;
			}
		}
	}
}

//敵の描画
void drawEnemy()
{
	for (int i = 0; i < enemy_num; i++) {
		if (enemy[i].enable == true) {
			DrawCircle(enemy[i].x, enemy[i].y, enemy[i].r, enemy[i].color, enemy[i].fill);
		}
	}
}
//弾が撃てるか確認する関数
bool canEnemyShot(Object enemy)
{
	//銃が冷えている
	if (enemy.cooltime <= 0) {
		if(enemy.x >=0 &&
			enemy.x < 800 &&
			enemy.y>0 &&
			enemy.y < 600)
		{
			//画面の中にいる
			return true;
		}
	}

	return false;
}