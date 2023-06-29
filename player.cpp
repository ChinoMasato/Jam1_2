//プレイヤーを操作する関数を書いたファイル
#include "en.h"
#include "DxLib.h"
#include "shot.h"
#include "player.h"

En player;//プレイヤー
int shotse;//ショットSE
//プレイヤーの初期化
void initPlayer()
{
	shotse = LoadSoundMem("maou_se_battle16.mp3");
	player.x = 100;
	player.y = 200;
	player.r = 10;
	player.color = GetColor(255, 255, 255);
	player.fill = true;
	player.cooltime = 0;
}

//プレイヤーの更新
void updatePlayer()
{
	//プレイヤーを動かす
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		player.x = player.x + 1.0;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		player.x = player.x - 1.0;
	}
	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		player.y = player.y - 1.0;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		player.y = player.y + 1.0;
	}
	if (player.x < 0) {
		//もし左端に出たら
		player.x = 0;
	}
	if (player.x >= 800) {
		//もし右端に出たら
		player.x = 800;
	}
	if (player.y < 0) {
		//もし左端に出たら
		player.y = 0;
	}
	if (player.y >= 600) {
		//もし右端に出たら
		player.y = 600;
	}

	//弾を撃つ処理
	if (CheckHitKey(KEY_INPUT_Z) == 1 &&
		player.cooltime <= 0)
	{
		//弾が無効なときのみ初期値をセットし有効にする
		for (int i = 0; i < ShotNum; i++)
		{
			//撃てる弾をみつける
			if (shot[i].enable == false) {
				//弾を撃つ
				shot[i].x = player.x;
				shot[i].y = player.y;
				shot[i].enable = true;
				player.cooltime = 30;//連射速度　小さいほど連射できる
				PlaySoundMem(shotse, DX_PLAYTYPE_BACK);
				break;
			}
		}
	}
	//銃を冷やす処理
	if (player.cooltime > 0) {
		player.cooltime--;
	}
}

//プレイヤーの描画
void drawPlayer()
{
	DrawCircle(player.x, player.y, player.r, player.color, player.fill);
}