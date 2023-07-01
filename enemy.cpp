#include "en.h"
#include "DxLib.h"
#include <math.h>
#include "shot.h"
#include "enemyshot.h"
#include "enemy.h"
#include "player.h"
#include "game.h"
#include "init.h"
#include "effect.h"

extern bool gameOverFlag;//ゲームオーバー判定
extern int stage;
extern int i;
extern double speed;
extern double dx;
extern double dy;
extern double d;
extern int boss_defeat_num;
extern int start;
extern int enemy_num;
extern int zenmetu;
extern int count;
extern int q;
extern int score;
extern int result;
extern int boss_action;
extern int j;
extern int action;
extern int one_second;
extern GameScene scene;

En enemy[20];//敵
//敵の初期化
void initEnemy()
{
	//敵画像の読み込み
	enemyimg = LoadGraph("enemy_1_1.png");
	if (stage >= 1 && stage <= 2)
	{
		//敵の初期化処理
		for (i = 0; i < 2 * stage; i++) { //赤(ショット有り)
			enemy[i].x = GetRand(499) + 300;
			enemy[i].y = GetRand(599);
			enemy[i].r = GetRand(10) + 30;
			enemy[i].color = GetColor(255, 0, 0);
			enemy[i].fill = true;
			enemy[i].vx = 1.0;//xの移動量
			enemy[i].vy = 1.0;//yの移動量
			enemy[i].enable = true;

			enemy[i].hp = 3 + boss_defeat_num;
			enemy[i].type = ENEMY1;
		}
		for (i = 2 * stage; i < 6 * stage; i++) { //緑
			enemy[i].x = GetRand(499) + 300;
			enemy[i].y = GetRand(599);
			enemy[i].r = GetRand(10) + 10;
			enemy[i].color = GetColor(0, 255, 0);
			enemy[i].fill = true;

			speed = 2.0;//速度
			dx = player.x - enemy[i].x;//プレイヤーと敵のx方向の距離
			dy = player.y - enemy[i].y;//プレイヤーと敵のy方向の距離
			d = sqrt(dx * dx + dy * dy);//敵とプレイヤーとの距離
			enemy[i].vx = speed * (dx / d);//xの移動量
			enemy[i].vy = speed * (dy / d);//yの移動量
			enemy[i].enable = true;

			enemy[i].hp = 1 + boss_defeat_num;
		}
		for (i = 6 * stage; i < 8 * stage; i++) { //青
			enemy[i].x = GetRand(499) + 300;
			enemy[i].y = GetRand(599);
			enemy[i].r = GetRand(10) + 5;
			enemy[i].color = GetColor(0, 0, 255);
			enemy[i].fill = true;

			enemy[i].vx = 5;//xの移動量
			enemy[i].vy = 5;//yの移動量
			enemy[i].enable = true;

			enemy[i].hp = 1 + boss_defeat_num;
		}
		for (i = 8 * stage; i < 10 * stage; i++) { //紫(ショット有り)
			enemy[i].x = GetRand(499) + 300;
			enemy[i].y = GetRand(599);
			enemy[i].r = GetRand(10) + 20;
			enemy[i].color = GetColor(167, 87, 168);
			enemy[i].fill = true;

			enemy[i].vx = 1.5;//xの移動量
			enemy[i].vy = 1.5;//yの移動量
			enemy[i].enable = true;

			enemy[i].hp = 2 + boss_defeat_num;
			enemy[i].type = ENEMY2;
		}
	}
	if (stage == 3)
	{
		//ボス(赤)
		i = 0;
		enemy[i].x = 700;
		enemy[i].y = GetRand(599);
		enemy[i].r = 50;
		enemy[i].color = GetColor(255, 0, 0);
		enemy[i].fill = true;
		enemy[i].vx = 0.0;//xの移動量
		enemy[i].vy = 1.0;//yの移動量
		enemy[i].enable = true;

		enemy[i].hp = 30 * (boss_defeat_num + 1);
		enemy[i].type = ENEMY3;

		//ボスのファンネル(弾は黄色、本体は青色)
		for (i = 1; i < 5 + boss_defeat_num; i++)
		{
			enemy[i].x = 600;
			enemy[i].y = GetRand(599);
			enemy[i].r = 15;
			enemy[i].color = GetColor(0, 0, 255);
			enemy[i].fill = true;
			enemy[i].vx = 3.0;//xの移動量
			enemy[i].vy = 3.0;//yの移動量
			enemy[i].enable = true;

			enemy[i].hp = 2 + boss_defeat_num;
			enemy[i].type = ENEMY2;
			enemy[i].action = GetRand(5);
		}
	}
}

//真っすぐ弾を撃つ
void straightShot(int rad, En ene)
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
			enemyshot[j].type = ene.type;
			enemyshot[j].vvx = enemyshot[j].vx * 0.01;
			enemyshot[j].vvy = enemyshot[j].vy * 0.01;
			break;
		}
	}
}

//狙って撃つ
void aimShot(En ene)
{
	//弾を撃てる状態
//弾が無効なときのみ初期値をセットし有効にする
	for (int j = 0; j < EnemyShotNum; j++)
	{
		//撃てる弾をみつける
		if (enemyshot[j].enable == false) {
			//弾を撃つ
			enemyshot[j].x = ene.x;
			enemyshot[j].y = ene.y;

			double speed = 1.0;//速度
			double dx = player.x - ene.x;//プレイヤーと敵のx方向の距離
			double dy = player.y - ene.y;//プレイヤーと敵のy方向の距離
			double d = sqrt(dx * dx + dy * dy);//敵とプレイヤーとの距離
			enemyshot[j].vx = speed * (dx / d);//xの移動量
			enemyshot[j].vy = speed * (dy / d);//yの移動量
			enemyshot[j].enable = true;
			enemyshot[j].type = ene.type;
			enemyshot[j].vvx = enemyshot[j].vx * 0.01;
			enemyshot[j].vvy = enemyshot[j].vy * 0.01;
			enemyshot[j].aim_time = one_second * 2;
			break;
		}
	}
}

//2列で撃つ
void twinShot(int rad, En ene, int q)
{
	//弾が無効なときのみ初期値をセットし有効にする
	for (int j = 0; j < EnemyShotNum; j++)
	{
		//撃てる弾をみつける
		if (enemyshot[j].enable == false) {
			//弾を撃つ
			double PI = 3.14159265358979323846264338;
			double minrad = PI / 180.0;//1度のラジアン
			double speed = 3.0;//速度
			enemyshot[j].x = ene.x;
			enemyshot[j].y = ene.y - 15 + (q * 30);
			enemyshot[j].vx = speed * cos(minrad * rad);
			enemyshot[j].vy = speed * sin(minrad * rad);
			enemyshot[j].enable = true;
			break;
		}
	}
}

//爆発発生関数
void explosion(En ene)
{
	for (i = 0; i < EffectNum; i++)
	{
		if (effe[i].enable == false)
		{
			effe[i].enable = true;
			effe[i].x = ene.x - 60;
			effe[i].y = ene.y - 60;
			effe[i].animeNo = 0;
			break;
		}
	}
}

//敵の更新
void updateEnemy()
{
	if (start == 0)
	{
		scene = Game;
		if (stage >= 1 && stage <= 2)
		{
			enemy_num = 10 * stage;
			for (int i = 0; i < enemy_num; i++) {
				if (enemy[i].enable == true) {
					//敵を自動で動かす
					if (i >= 0 && i < 6 * stage) //追尾型(緑色)の動き
					{
						dx = player.x - enemy[i].x;//プレイヤーと敵のx方向の距離
						dy = player.y - enemy[i].y;//プレイヤーと敵のy方向の距離
						d = sqrt(dx * dx + dy * dy);//敵とプレイヤーとの距離
						enemy[i].vx = speed * (dx / d);//xの移動量
						enemy[i].vy = speed * (dy / d);//yの移動量
					}
					if (i >= 8 * stage && i < 10 * stage) //ランダム型(紫色)の動き1
					{
						if (count % (one_second * 5) == 0)
						{
							enemy[i].action = GetRand(3);
						}
						if (enemy[i].action == 3)
						{
							enemy[i].vx = enemy[i].vx * -1;
						}
						if (enemy[i].action == 2)
						{
							enemy[i].vy = enemy[i].vy * -1;
						}
						if (enemy[i].action == 1)
						{
							enemy[i].vx = enemy[i].vx * -1;
							enemy[i].vy = enemy[i].vy * -1;
						}
					}
					enemy[i].x += enemy[i].vx;
					enemy[i].y += enemy[i].vy;

					if (enemy[i].x < 0 || enemy[i].x >= 800) {
						//もし左端・右端に出たら
						enemy[i].vx = enemy[i].vx * -1;
					}
					if (enemy[i].y < 0 || enemy[i].y >= 600) {
						//もし上端・下端に出たら
						enemy[i].vy = enemy[i].vy * -1;
					}

					if (i >= 0 && i < 2 * stage || i >= 8 * stage && i < 10 * stage)
					{
						//弾を発射する
						if (canEnemyShot(enemy[i]))
						{
							if (enemy[i].type == ENEMY1) {
								straightShot(180, enemy[i]);
								enemy[i].cooltime = one_second * 2;//連射速度　小さいほど連射できる
							}
							if (enemy[i].type == ENEMY2) {
								aimShot(enemy[i]);
								enemy[i].cooltime = one_second * 3;//連射速度　小さいほど連射できる
							}
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
									if (gameOverFlag == false)
									{
										if (i >= 0 && i < 2 * stage) {
											score += 1;
										}
										if (i >= 2 * stage && i < 6 * stage) {
											score += 3;
										}
										if (i >= 6 * stage && i < 8 * stage) {
											score += 8;
										}
										if (i >= 8 * stage && i < 10 * stage) {
											score += 5;
										}
										zenmetu++;
									}
									
									if (zenmetu == enemy_num)
									{
										start = 1;
										count = 0;
										result = 1;
									}
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
		if (stage == 3)
		{
			enemy_num = 5 + boss_defeat_num;
			for (i = 0; i < enemy_num; i++)
			{
				if (enemy[i].enable == true)
				{
					if (i == 0) //ボスの動き
					{
						enemy[i].y += enemy[i].vy;
					}
					if (i >= 1 && i < enemy_num) //ファンネルの動き
					{
						if (count % (one_second * 5) == 0)
						{
							enemy[i].action = GetRand(3);
						}
						if (enemy[i].action == 3) //ボスファンネルの動き1-1(通常)
						{
							enemy[i].vx = enemy[i].vx * -1;
						}
						if (enemy[i].action == 2) //ボスファンネルの動き1-2(通常)
						{
							enemy[i].vy = enemy[i].vy * -1;
						}
						if (enemy[i].action == 1)
						{
							enemy[i].vx = enemy[i].vx * -1;
							enemy[i].vy = enemy[i].vy * -1;
						}
						enemy[i].x += enemy[i].vx;
						enemy[i].y += enemy[i].vy;
					}

					if (enemy[i].x < 0 || enemy[i].x >= 800) {
						//もし左端・右端に出たら
						enemy[i].vx = enemy[i].vx * -1;
					}
					if (enemy[i].y < 0 || enemy[i].y >= 600) {
						//もし上端・下端に出たら
						enemy[i].vy = enemy[i].vy * -1;
					}

					//弾を発射する
					if (canEnemyShot(enemy[i]))
					{
						if (enemy[i].type == ENEMY3) {
							for (q = 0; q < 2; q++)
							{
								twinShot(180, enemy[i], q);
							}
							enemy[i].cooltime = one_second * 1;//連射速度　小さいほど連射できる
						}
						if (enemy[i].type == ENEMY2) {
							aimShot(enemy[i]);
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
									if (gameOverFlag == false)
									{
										StopMusic();
										PlayMusic("STG_gameover.mp3", DX_PLAYTYPE_LOOP);
										PlaySoundFile("STG_enemy_defeat.mp3", DX_PLAYTYPE_BACK);
										explosion(enemy[i]);//爆発
									}
									player.color = enemyshot[i].color;
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
										if (enemy[i].type == ENEMY3)
										{
											PlaySoundFile("STG_boss_defeat.mp3", DX_PLAYTYPE_BACK);
										}
										if (enemy[i].type == ENEMY2)
										{
											PlaySoundFile("STG_enemy_defeat.mp3", DX_PLAYTYPE_BACK);
										}
										explosion(enemy[i]);//爆発
									}
									enemy[i].enable = false;//敵を無効
									if (gameOverFlag == false)
									{
										if (enemy[i].type == ENEMY3)
										{
											zenmetu = enemy_num;
											score += 30 * (boss_defeat_num + 1);
										}
										if (enemy[i].type == ENEMY2)
										{
											score += 5;
										}
									}

									if (zenmetu == enemy_num)
									{
										for (q = 0; q < enemy_num; q++)
										{
											if (enemy[i].type == ENEMY2)
											{
												enemy[i].enable = false;//敵を無効
											}
										}
										start = 1;
										count = 0;
										result = 1;
									}
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
	}
	
}

//敵の描画
void drawEnemy()
{
	if (start == 0)
	{
		for (int i = 0; i < enemy_num; i++) {
			if (enemy[i].enable == true) {
				DrawGraph(enemy[i].x - 24, enemy[i].y - 24, enemyimg, true);
				//DrawCircle(enemy[i].x, enemy[i].y, enemy[i].r, enemy[i].color, enemy[i].fill);
			}
		}
	}
}
//弾が撃てるか確認する関数
bool canEnemyShot(En enemy)
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