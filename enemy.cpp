#include "_system.h"
#include "DxLib.h"
#include <math.h>
#include "player_shot.h"
#include "enemyshot.h"
#include "enemy.h"
#include "player.h"
//#include "game.h"
//#include "effect.h"

extern int gameOverFlag;//ゲームオーバー判定
extern int stage;
int i;
double speed;
double accel;
extern double dx;
extern double dy;
extern double d;
extern const int enemy_num;
extern int count;
int q;
extern int score;
extern int result;
extern int j;
extern int action;
extern int one_second;
extern int time;

Object enemy[enemy_num];//敵
//敵の初期化
void initEnemy()
{
	SRand(time);
	//敵画像の読み込み
	enemyimg = LoadGraph("enemy.png");
	shipimg = LoadGraph("battleship_02.png");
	canon_1_leftimg = LoadGraph("canon_1_big_left.png");
	canon_1_rightimg = LoadGraph("canon_1_big_right.png");
	canon_2_leftimg = LoadGraph("canon_2_left.png");
	canon_2_rightimg = LoadGraph("canon_2_right.png");
	canon_3_left_upimg = LoadGraph("canon_3_left_up.png");
	canon_3_right_upimg = LoadGraph("canon_3_right_up.png");
	canon_3_left_downimg = LoadGraph("canon_3_left_down.png");
	canon_3_right_downimg = LoadGraph("canon_3_right_down.png");
	bossimg = LoadGraph("boss.png");

	sys[0].se_break = LoadSoundMem("tyun.mp3");
	//敵の初期化処理
	for (i = 0; i < 10; i++) {
		enemy[i].x = GetRand(799);
		enemy[i].y = -300 - i * 100;
		enemy[i].r = 25;
		enemy[i].vx = 0.0;//xの移動量
		enemy[i].vy = 2.0;//yの移動量
		enemy[i].enable = true;

		enemy[i].hp = 2;
		enemy[i].enemytype = ENEMY1;
	}
	for (i = 10; i < 30; i++) {
		speed = 3.0;
		accel = 50.0;
		enemy[i].rad = (i - 10) * 18;
		enemy[i].y = -1800 - (i - 10) * 100;
		enemy[i].x = 400;
		enemy[i].r = 25;
		enemy[i].vx = accel * cos(enemy[i].rad);//xの移動量
		enemy[i].vy = speed;
		enemy[i].enable = true;

		enemy[i].hp = 2;
		enemy[i].enemytype = ENEMY2;
	}
	for (i = 30; i < 45; i++) {
		enemy[i].y = -2300 - (i - 30) * 100;
		enemy[i].x = GetRand(799);
		enemy[i].r = 25;
		enemy[i].vx = GetRand(4);//xの移動量
		enemy[i].vy = 3.0;//yの移動量
		enemy[i].enable = true;

		enemy[i].hp = 2;
		enemy[i].enemytype = ENEMY3;
	}
	for (i = 45; i < 47; i++) {
		enemy[i].y = -6000;
		enemy[i].x = -(221 / 2) + (i - 45) * 800;
		enemy[i].vx = 0.0;//xの移動量
		enemy[i].vy = 4.0;//yの移動量
		enemy[i].enable = true;
		enemy[i].enemytype = SHIP;

		enemy[i].hp = 2;
	}
	for (i = 47; i < 49; i++) {
		enemy[i].y = -6000 + 300 - 50;
		enemy[i].x = 221 - 181 + (i - 47) * (720 - 152);
		enemy[i].vx = 0.0;//xの移動量
		enemy[i].vy = 4.0;//yの移動量
		enemy[i].enable = true;
		enemy[i].enemytype = CANON1;
		if (i == 47)
		{
			enemy[i].place = LEFT_UP;
		}
		if (i == 48)
		{
			enemy[i].place = RIGHT_UP;
		}

		enemy[i].hp = 2;
	}
	for (i = 49; i < 51; i++) {
		enemy[i].y = -6000 + 300 - 50 - 50 - 50;//上側
		enemy[i].x = 221 - (181 + 20) + (i - 49) * (760 - 66);
		enemy[i].vx = 0.0;//xの移動量
		enemy[i].vy = 4.0;//yの移動量
		enemy[i].enable = true;
		enemy[i].enemytype = CANON2;
		if (i == 49)
		{
			enemy[i].place = LEFT_UP;
		}
		if (i == 50)
		{
			enemy[i].place = RIGHT_UP;
		}

		enemy[i].hp = 2;
	}
	for (i = 51; i < 53; i++) {
		enemy[i].y = -6000 + 300 - (-50 - 50);//下側
		enemy[i].x = 221 - (181 + 20) + (i - 51) * (760 - 66);
		enemy[i].vx = 0.0;//xの移動量
		enemy[i].vy = 4.0;//yの移動量
		enemy[i].enable = true;
		enemy[i].enemytype = CANON2;
		if (i == 51)
		{
			enemy[i].place = LEFT_DOWN;
		}
		if (i == 52)
		{
			enemy[i].place = RIGHT_DOWN;
		}

		enemy[i].hp = 2;
	}
	for (i = 53; i < 55; i++) {
		enemy[i].y = -6000 + 300 -(50 * 4) - 70;//上側
		enemy[i].x = 221 - (181 + 30) + (i - 53) * (780 - 79);
		enemy[i].vx = 0.0;//xの移動量
		enemy[i].vy = 4.0;//yの移動量
		enemy[i].enable = true;
		enemy[i].enemytype = CANON3;
		if (i == 53)
		{
			enemy[i].place = LEFT_UP;
		}
		if (i == 54)
		{
			enemy[i].place = RIGHT_UP;
		}

		enemy[i].hp = 2;
	}
	for (i = 55; i < 57; i++) {
		enemy[i].y = -6000 + 300 + 50 * 4;//下側
		enemy[i].x = 221 - (181 + 30) + (i - 55) * (780 - 79);
		enemy[i].vx = 0.0;//xの移動量
		enemy[i].vy = 4.0;//yの移動量
		enemy[i].enable = true;
		enemy[i].enemytype = CANON3;
		if (i == 55)
		{
			enemy[i].place = LEFT_DOWN;
		}
		if (i == 56)
		{
			enemy[i].place = RIGHT_DOWN;
		}

		enemy[i].hp = 2;
	}
	//ボス
	for (i = 57; i < 58; i++) {
		enemy[i].y = -930;
		enemy[i].x = 400 - 150;
		enemy[i].r = 150;
		enemy[i].vx = GetRand(3) + 3;//xの移動量
		enemy[i].vy = 4.0;//yの移動量
		enemy[i].enable = true;

		enemy[i].hp = 200;
		enemy[i].enemytype = BOSS;
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
			if (ene.enemytype == ENEMY1 || ene.enemytype == ENEMY2 || ene.enemytype == ENEMY3)
			{
				enemyshot[j].x = ene.x + 23;
				enemyshot[j].y = ene.y + 52;
			}
			if (ene.enemytype == CANON3)
			{
				if (ene.place == LEFT_UP)
				{
					enemyshot[j].x = ene.x + 79;
					enemyshot[j].y = ene.y + 35 + 10;
				}
				if (ene.place == LEFT_DOWN)
				{
					enemyshot[j].x = ene.x + 79;
					enemyshot[j].y = ene.y + 35 - 20;
				}
				if (ene.place == RIGHT_UP)
				{
					enemyshot[j].x = ene.x;
					enemyshot[j].y = ene.y + 35 + 10;
				}
				if (ene.place == RIGHT_DOWN)
				{
					enemyshot[j].x = ene.x;
					enemyshot[j].y = ene.y + 35 - 20;
				}
			}
			if (ene.enemytype == BOSS)
			{
				enemyshot[j].x = ene.x + 150;
				enemyshot[j].y = ene.y + 300;
			}
			double PI = 3.14159265358979323846264338;
			double minrad = PI / 180.0;//1度のラジアン
			double speed = 5.0;//速度
			enemyshot[j].vx = speed * cos(minrad * rad);
			enemyshot[j].vy = speed * sin(minrad * rad);
			enemyshot[j].enable = true;
			enemyshot[j].enemytype = ene.enemytype;
			enemyshot[j].vvx = enemyshot[j].vx * 0.03;
			enemyshot[j].vvy = enemyshot[j].vy * 0.03;
			enemyshot[j].enemyshottype = NORMAL;
			break;
		}
	}
}

//狙って撃つ
void aimShot(Object ene)
{
	//弾を撃てる状態
//弾が無効なときのみ初期値をセットし有効にする
	for (int j = 0; j < EnemyShotNum; j++)
	{
		//撃てる弾をみつける
		if (enemyshot[j].enable == false) {
			//弾を撃つ
			if (ene.enemytype == ENEMY1 || ene.enemytype == ENEMY2 || ene.enemytype == ENEMY3)
			{
				enemyshot[j].x = ene.x + 23;
				enemyshot[j].y = ene.y + 52;
			}
			double speed = 4.0;//速度
			double dx = pl.x - ene.x;//プレイヤーと敵のx方向の距離
			double dy = pl.y - ene.y;//プレイヤーと敵のy方向の距離
			double d = sqrt(dx * dx + dy * dy);//敵とプレイヤーとの距離
			enemyshot[j].vx = speed * (dx / d);//xの移動量
			enemyshot[j].vy = speed * (dy / d);//yの移動量
			enemyshot[j].enable = true;
			enemyshot[j].enemytype = ene.enemytype;
			enemyshot[j].vvx = enemyshot[j].vx * 0.01;
			enemyshot[j].vvy = enemyshot[j].vy * 0.01;
			enemyshot[j].aim_time = one_second * 3;
			enemyshot[j].enemyshottype = NORMAL;
			break;
		}
	}
}

//狙って撃つ＋爆発する
void missileShot(Object ene, int q)
{
	//弾を撃てる状態
//弾が無効なときのみ初期値をセットし有効にする
	for (int j = 0; j < EnemyShotNum; j++)
	{
		//撃てる弾をみつける
		if (enemyshot[j].enable == false) {
			//弾を撃つ
			if (ene.place == LEFT_UP)
			{
				enemyshot[j].x = ene.x + 152;
				enemyshot[j].y = ene.y + 50;
				enemyshot[j].bombtime = 120;
				enemyshot[j].aim_time = one_second * 2;
				enemyshot[j].vvx = enemyshot[j].vx * 0.03;
				enemyshot[j].vvy = enemyshot[j].vy * 0.03;
			}
			if (ene.place == RIGHT_UP)
			{
				enemyshot[j].x = ene.x;
				enemyshot[j].y = ene.y + 50;
				enemyshot[j].bombtime = 120;
				enemyshot[j].aim_time = one_second * 2;
				enemyshot[j].vvx = enemyshot[j].vx * 0.03;
				enemyshot[j].vvy = enemyshot[j].vy * 0.03;
			}
			if (ene.enemytype == BOSS)
			{
				enemyshot[j].x = ene.x + 30 + (q - 1) * 240;
				enemyshot[j].y = ene.y + 200;
				enemyshot[j].bombtime = 120;
				enemyshot[j].aim_time = one_second * 2;
				enemyshot[j].vvx = enemyshot[j].vx * 0.05;
				enemyshot[j].vvy = enemyshot[j].vy * 0.05;
			}

			double speed = 3.0;//速度
			double dx = pl.x - ene.x;//プレイヤーと敵のx方向の距離
			double dy = pl.y - ene.y;//プレイヤーと敵のy方向の距離
			double d = sqrt(dx * dx + dy * dy);//敵とプレイヤーとの距離
			enemyshot[j].vx = speed * (dx / d);//xの移動量
			enemyshot[j].vy = speed * (dy / d);//yの移動量
			enemyshot[j].enable = true;
			enemyshot[j].enemytype = ene.enemytype;
			enemyshot[j].enemyshottype = BOMB_MOVE;
			break;
		}
	}
}

//2列で撃つ
void twinShot(int rad, Object ene, int q)
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
			if (ene.place == LEFT_UP || ene.place == LEFT_DOWN)
			{
				enemyshot[j].x = ene.x + 66;
			}
			if (ene.place == RIGHT_UP || ene.place == RIGHT_DOWN)
			{
				enemyshot[j].x = ene.x;
			}
			enemyshot[j].y = ene.y - 15 + (q * 30) + 25;
			enemyshot[j].vx = speed * cos(minrad * rad);
			enemyshot[j].vy = speed * sin(minrad * rad);
			enemyshot[j].enable = true;
			enemyshot[j].enemyshottype = NORMAL;
			break;
		}
	}
}

//ビームを撃つ
void Beam(int rad, Object ene)
{
	//弾が無効なときのみ初期値をセットし有効にする
	for (int j = 0; j < EnemyShotNum; j++)
	{
		//撃てる弾をみつける
		if (enemyshot[j].enable == false) {
			//弾を撃つ
			if (ene.enemytype == BOSS)
			{
				enemyshot[j].x = ene.x + 150;
				enemyshot[j].y = ene.y + 300;
			}
			double PI = 3.14159265358979323846264338;
			double minrad = PI / 180.0;//1度のラジアン
			double speed = 5.0;//速度
			enemyshot[j].vx = speed * cos(minrad * rad);
			enemyshot[j].vy = speed * sin(minrad * rad);
			enemyshot[j].enable = true;
			enemyshot[j].enemytype = ene.enemytype;
			enemyshot[j].vvx = enemyshot[j].vx * 0.0;
			enemyshot[j].vvy = enemyshot[j].vy * 0.0;
			enemyshot[j].enemyshottype = BEAM_STANDBY;
			enemyshot[j].standbytime_B = 1000;
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
			if (enemy[i].enemytype == ENEMY1)
			{
				enemy[i].x += enemy[i].vx;
				enemy[i].y += enemy[i].vy;
				//弾を発射する
				if (canEnemyShot(enemy[i]))
				{
					straightShot(90, enemy[i]);
					enemy[i].cooltime = one_second * 2;//連射速度　小さいほど連射できる
				}
			}
			if (enemy[i].enemytype == ENEMY2)
			{
				enemy[i].rad += 0.15;
				enemy[i].vx = accel * cos(enemy[i].rad);//xの移動量
				enemy[i].x += enemy[i].vx;
				enemy[i].y += enemy[i].vy;
			}
			if (enemy[i].enemytype == ENEMY3)
			{
				enemy[i].x += enemy[i].vx;
				enemy[i].y += enemy[i].vy;
				//弾を発射する
				if (canEnemyShot(enemy[i]))
				{
					aimShot(enemy[i]);
					enemy[i].cooltime = one_second * 2;//連射速度　小さいほど連射できる
				}
			}
			if (enemy[i].enemytype == SHIP || enemy[i].enemytype == CANON1
				|| enemy[i].enemytype == CANON2 || enemy[i].enemytype == CANON3)
			{
				if (time < 25 || time > 35)
				{
					enemy[i].y += enemy[i].vy;
				}
				if (time >= 25 && time <= 35)
				{
					//弾を発射する
					if (canEnemyShot(enemy[i]))
					{
						if (enemy[i].enemytype == CANON1) {
							missileShot(enemy[i], 0);
							enemy[i].cooltime = one_second * 2;//連射速度　小さいほど連射できる
						}
						if (enemy[i].enemytype == CANON2) {
							if (enemy[i].place == LEFT_UP || enemy[i].place == LEFT_DOWN)
							{
								for (q = 0; q < 2; q++)
								{
									twinShot(0, enemy[i], q);
								}
							}
							if (enemy[i].place == RIGHT_UP || enemy[i].place == RIGHT_DOWN)
							{
								for (q = 0; q < 2; q++)
								{
									twinShot(180, enemy[i], q);
								}
							}
							enemy[i].cooltime = one_second * 1;//連射速度　小さいほど連射できる
						}
						if (enemy[i].enemytype == CANON3) {
							if (enemy[i].place == LEFT_UP)
							{
								for (q = 0; q < 3; q++)
								{
									straightShot(0 + q * 30, enemy[i]);
								}
							}
							if (enemy[i].place == RIGHT_UP)
							{
								for (q = 0; q < 3; q++)
								{
									straightShot(120 + q * 30, enemy[i]);
								}
							}
							if (enemy[i].place == LEFT_DOWN)
							{
								for (q = 0; q < 3; q++)
								{
									straightShot(300 + q * 30, enemy[i]);
								}
							}
							if (enemy[i].place == RIGHT_DOWN)
							{
								for (q = 0; q < 3; q++)
								{
									straightShot(180 + q * 30, enemy[i]);
								}
							}
							enemy[i].cooltime = one_second * 2;//連射速度　小さいほど連射できる
						}
					}
				}
			}
			if (enemy[i].enemytype == BOSS)
			{
				if (enemy[i].y < 0 && enemy[46].y >= 700)
				{
					enemy[i].y += enemy[i].vy;
				}
				if (enemy[i].y >= 0)
				{
					enemy[i].x += enemy[i].vx;
					if (canBossShot_M(enemy[i]))
					{
						missileShot(enemy[i], 1);
						missileShot(enemy[i], 2);
						enemy[i].boss_cooltime_M = one_second / 2;//連射速度　小さいほど連射できる
					}
					if (canBossShot_S(enemy[i]))
					{
						for (q = 0; q < 3; q++)
						{
							straightShot(75 + q * 15, enemy[i]);
						}
						enemy[i].boss_cooltime_S = one_second / 3;//連射速度　小さいほど連射できる
					}
				}
			}
			if (enemy[i].x < 0 || enemy[i].x >= 800) {
				//もし左端・右端に出たら
				enemy[i].vx = enemy[i].vx * -1;
			}

			if (isHit(pl, enemy[i]))
			{
				//当たっている
				if (enemy[i].enable == true && pl.muteki_time <= 0)
				{
					gameOverFlag++;
					pl.muteki_time = one_second * 1; //60毎フレーム*3=180→3秒間無敵時間ができる
				}
			}

			for (int j = 0; j < ps_; j++) {
				//敵と弾との当たり判定
				if (ps[j].live == true) {
					if (isHit(ps[j], enemy[i]))
					{
						//当たっている
						if (enemy[i].hp > 0)
						{
							if (enemy[i].enemytype == ENEMY1 || enemy[i].enemytype == ENEMY2
								|| enemy[i].enemytype == ENEMY3 || enemy[i].enemytype == BOSS)
							{
								enemy[i].hp--;
								ps[j].live = false;
							}
						}
						if (enemy[i].hp <= 0)
						{
							if (enemy[i].enable == true)
							{

								PlaySoundMem(sys[0].se_break, DX_PLAYTYPE_BACK);
								if (enemy[i].enemytype == ENEMY1)
								{
									score += 10;
								}
								if (enemy[i].enemytype == ENEMY2)
								{
									score += 30;
								}
								if (enemy[i].enemytype == ENEMY3)
								{
									score += 20;
								}
								if (enemy[i].enemytype == BOSS)
								{
									score += 50;
									score -= gameOverFlag * 5;
								}
								//explosion(enemy[i]);//爆発
							}
							enemy[i].enable = false;//敵を無効
						}
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
	for (int i = 0; i < EnemyShotNum; i++)
	{
		//ボムが爆発するまでカウントダウンする
		if (enemyshot[i].bombtime > 0)
		{
			enemyshot[i].bombtime--;
		}
		
		if (enemy[i].boss_cooltime_M > 0) {
			enemy[i].boss_cooltime_M--;
		}
	
		if (enemy[i].boss_cooltime_S > 0) {
			enemy[i].boss_cooltime_S--;
		}
	}
}

//敵の描画
void drawEnemy()
{
	for (int i = 0; i < enemy_num; i++) {
		if (enemy[i].enable == true) {
			if (enemy[i].enemytype == ENEMY1 || enemy[i].enemytype == ENEMY2 || enemy[i].enemytype == ENEMY3)
			{
				DrawGraph(enemy[i].x, enemy[i].y, enemyimg, true);
			}
			if (enemy[i].enemytype == SHIP)
			{
				DrawGraph(enemy[i].x, enemy[i].y, shipimg, true);
			}
			if (enemy[i].enemytype == CANON1)
			{
				if (enemy[i].place == LEFT_UP)
				{
					DrawGraph(enemy[i].x, enemy[i].y, canon_1_leftimg, true);
				}
				if (enemy[i].place == RIGHT_UP)
				{
					DrawGraph(enemy[i].x, enemy[i].y, canon_1_rightimg, true);
				}
			}
			if (enemy[i].enemytype == CANON2)
			{
				if (enemy[i].place == LEFT_UP || enemy[i].place == LEFT_DOWN)
				{
					DrawGraph(enemy[i].x, enemy[i].y, canon_2_leftimg, true);
				}
				if (enemy[i].place == RIGHT_UP || enemy[i].place == RIGHT_DOWN)
				{
					DrawGraph(enemy[i].x, enemy[i].y, canon_2_rightimg, true);
				}
			}
			if (enemy[i].enemytype == CANON3)
			{
				if (enemy[i].place == LEFT_UP)
				{
					DrawGraph(enemy[i].x, enemy[i].y, canon_3_left_upimg, true);
				}
				if (enemy[i].place == RIGHT_UP)
				{
					DrawGraph(enemy[i].x, enemy[i].y, canon_3_right_upimg, true);
				}
				if (enemy[i].place == LEFT_DOWN)
				{
					DrawGraph(enemy[i].x, enemy[i].y, canon_3_left_downimg, true);
				}
				if (enemy[i].place == RIGHT_DOWN)
				{
					DrawGraph(enemy[i].x, enemy[i].y, canon_3_right_downimg, true);
				}
			}
			if (enemy[i].enemytype == BOSS)
			{
				DrawGraph(enemy[i].x, enemy[i].y, bossimg, true);
			}

			//--------------------------------
			//DrawCircle(enemy[i].x, enemy[i].y, enemy[i].r, GetColor(0, 255, 0), true);
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
bool canBossShot_M(Object enemy)
{
	if (enemy.boss_cooltime_M <= 0)
	{
		if (enemy.x >= 0 &&
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
bool canBossShot_S(Object enemy)
{
	if (enemy.boss_cooltime_S <= 0)
	{
		if (enemy.x >= 0 &&
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
bool canBossShot_B(Object enemy)
{
	if (enemy.boss_cooltime_B <= 0)
	{
		if (enemy.x >= 0 &&
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