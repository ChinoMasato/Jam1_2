//プレイヤーの弾を操作する関数を書いたファイル
#include "en.h"
#include "DxLib.h"
#include "shot.h"

En shot[ShotNum];//弾
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
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 127);//半透明
			DrawCircle(shot[i].x, shot[i].y, shot[i].r, shot[i].color, shot[i].fill);	
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//不透明
			DrawCircle(shot[i].x, shot[i].y, shot[i].r * 0.5, shot[i].color, shot[i].fill);

		}
	}
}