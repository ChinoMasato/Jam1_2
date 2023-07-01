//プレイヤーの弾を操作する関数を書いたファイル
#include "_system.h"
#include "DxLib.h"
#include "shot.h"
#include "enemy.h"
#include <math.h>

Object shot[ShotNum];//弾

//弾の初期化
void initShot()
{
	for (int i = 0; i < ShotNum; i++) {
		shot[i].r = 5;
		shot[i].color = GetColor(255, 0, 0);
		shot[i].fill = true;
		shot[i].vx = 5.0;
		shot[i].vy = 5.0;
		shot[i].enable = false;
	}
}
//弾の更新
void updateShot()
{
	//弾が有効なときに弾を動かす
	for (int i = 0; i < ShotNum; i++)
	{
		if (shot[i].enable == true) {

			shot[i].x += shot[i].vx * cos(shot[i].rad);
			shot[i].y += shot[i].vy * sin(shot[i].rad);
		}
		if (shot[i].x < 0 || shot[i].x > 800 || shot[i].y < 0 || shot[i].y > 600)
		{
			shot[i].enable = false;
		}
	}
}
//弾の描画
void drawShot()
{
	for (int i = 0; i < ShotNum; i++) {
		if (shot[i].enable == true)
		{
			if (shot[i].shottype == NORMAL)
			{
				//自機弾(通常)の画像
			}
			if (shot[i].shottype == BOMB)
			{
				//自機弾(ボム)の画像
				//ボムを爆発させる
				for (int j = 0; j < enemy_num; j++) 
				{
					if (shot[i].bombtime <= 60 && shot[i].bombtime >= 30 && isHit(shot[i], enemy[j]) == false)
					{
						DrawCircle(shot[i].x, shot[i].y, shot[i].r, shot[i].color, shot[i].fill);
						shot[i].bomb_x = shot[i].x;
						shot[i].bomb_y = shot[i].y;
						shot[i].r = 5;
					}
					if (shot[i].bombtime < 30 && shot[i].bombtime >= 0 || isHit(shot[i], enemy[j]) == true)
					{
						DrawCircle(shot[i].bomb_x, shot[i].bomb_y, shot[i].r, shot[i].color, shot[i].fill);
						shot[i].r++;
					}
					if (shot[i].r >= 25)
					{
						shot[i].enable = false;
					}
				}
			}
			if (shot[i].shottype == BEAM)
			{
				//自機弾(ビーム)の画像
			}
		}
	}
}