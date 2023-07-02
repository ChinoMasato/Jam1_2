#include "DxLib.h"
#include "player.h"
#include "shot.h"
#include "enemyshot.h"
#include "enemy.h"
#include "_system.h"
#include "backscreen.h"


void init();
void update();//�X�V�֐��̃v���g�^�C�v�錾
void draw();//�`�揈��

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

	init();//�����������̌Ăяo���@�N������x�����Ăяo��

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		up_back();
		draw_back();

		update();//�X�V�����̌Ăяo��

		//�h�b�g�`�揈��
		int color = GetColor(255, 255, 255);
		DrawPixel(400, 300, color);
		ScreenFlip();
		ClearDrawScreen();
	}

	DxLib_End();

	return 0;
}
//�������֐��@�����A�߂�l�Ȃ�
void init()
{

	init_back();
	//�v���C���[�̏�����
	initPlayer();
	//�e�̏�����
	initShot();
	initEnemyShot();
	//�G�̏���������
	initEnemy();
}

//�X�V�֐�
void update()
{
	//�v���C���[�̍X�V
	updatePlayer();
	//�e�̍X�V
	updateShot();
	updateEnemyShot();
	//�G�̍X�V
	updateEnemy();
	//�`�揈��
	draw();
	updateGame();

	DrawFormatString(0, 0, GetColor(255, 255, 0), "���Ԍo�� %d �b", time);
	DrawFormatString(0, 24, GetColor(255, 255, 0), "�Q�[���I�[�o�[ %d", gameOverFlag);
}

//�`�揈��
void draw()
{
	//�G�̕`��
	drawEnemy();
	//�v���C���[�̕`��
	drawPlayer();
	//�e�̕`��
	drawShot();
	drawEnemyShot();
}