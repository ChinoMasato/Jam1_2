#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(800, 600, 32);
	if (DxLib_Init() == -1)	
	{
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//ドット描画処理
		int color = GetColor(255, 255, 255);
		DrawPixel(400, 300, color);
		ScreenFlip();
		ClearDrawScreen();
	}

	DxLib_End();

	return 0;
}

