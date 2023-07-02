#include "DxLib.h"
#include "player.h"
#include "shot.h"
#include "enemyshot.h"
#include "enemy.h"
#include "_system.h"
#include "backscreen.h"


void init();
void update();//更新関数のプロトタイプ宣言
void draw();//描画処理

extern int time;
extern bool gameOverFlag;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(800, 600, 32);
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	init();//初期化処理の呼び出し　起動時一度だけ呼び出す

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		up_back();
		draw_back();

		update();//更新処理の呼び出し

		//ドット描画処理
		int color = GetColor(255, 255, 255);
		DrawPixel(400, 300, color);
		ScreenFlip();
		ClearDrawScreen();
	}

	DxLib_End();

	return 0;
}
//初期化関数　引数、戻り値なし
void init()
{

	init_back();
	//プレイヤーの初期化
	initPlayer();
	//弾の初期化
	initShot();
	initEnemyShot();
	//敵の初期化処理
	initEnemy();
}

//更新関数
void update()
{
	//プレイヤーの更新
	updatePlayer();
	//弾の更新
	updateShot();
	updateEnemyShot();
	//敵の更新
	updateEnemy();
	//描画処理
	draw();
	updateGame();

	DrawFormatString(0, 0, GetColor(255, 255, 0), "時間経過 %d 秒", time);
	DrawFormatString(0, 24, GetColor(255, 255, 0), "ゲームオーバー %d", gameOverFlag);
}

//描画処理
void draw()
{
	//敵の描画
	drawEnemy();
	//プレイヤーの描画
	drawPlayer();
	//弾の描画
	drawShot();
	drawEnemyShot();
}