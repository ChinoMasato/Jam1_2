#include "DxLib.h"
#include "player.h"
#include "player_shot.h"
#include "enemyshot.h"
#include "enemy.h"
#include "_system.h"
#include "backscreen.h"


void init();
void update();//更新関数のプロトタイプ宣言
void draw();//描画処理

extern int time;
extern int gameOverFlag;
extern int score;

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
	PlayMusic("Disturbance.mp3", DX_PLAYTYPE_LOOP);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		up_back();
		draw_back();

		if (scene == scene1)
		{
			scene_1();
		}
		if (scene == scene2)
		{
			scene_2();
		}
		if (scene == scene3)
		{
			scene_3();
			update();//更新処理の呼び出し
		}
		if (scene == scene4)
		{
			scene_4();
		}

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
	init_player();
	//弾の初期化
	init_player_shot();
	initEnemyShot();
	//敵の初期化処理
	initEnemy();
}

//更新関数
void update()
{
	//プレイヤーの更新
	up_player();
	//弾の更新
	up_player_shot();
	updateEnemyShot();
	//敵の更新
	updateEnemy();
	//描画処理
	draw();
	updateGame();

	DrawFormatString(0, 0, GetColor(255, 255, 0), "時間経過 %d 秒", time);
	DrawFormatString(0, 24, GetColor(255, 255, 0), "被弾 %d 回", gameOverFlag);
	//DrawFormatString(400, 48, GetColor(255, 255, 0), "スコア %d", score);
}

//描画処理
void draw()
{
	//弾の描画
	draw_player_shot();
	drawEnemyShot();
	//敵の描画
	drawEnemy();
	//プレイヤーの描画
	draw_player();
}