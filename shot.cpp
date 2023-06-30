//プレイヤーの弾を操作する関数を書いたファイル
#include "_system.h"
#include "DxLib.h"
#include "shot.h"
#include <math.h>

Object shot[ShotNum];//弾
//弾の初期化
void initShot()
{
	for (int i = 0; i < ShotNum; i++) {
		shot[i].r = 5;
		shot[i].color = GetColor(255, 255, 0);
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
			if (shot[i].type == NORMAL)
			{
				//自機弾(通常)の画像
			}
			if (shot[i].type == BOMB)
			{
				//自機弾(通常)の画像
			}
			if (shot[i].type == BEAM)
			{
				//自機弾(通常)の画像
			}
		}
	}
}