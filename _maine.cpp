#include "DxLib.h"
#include "player.h"
#include "player_shot.h"
#include "enemyshot.h"
#include "enemy.h"
#include "_system.h"
#include "backscreen.h"


void init();
void update();//�X�V�֐��̃v���g�^�C�v�錾
void draw();//�`�揈��

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

	init();//�����������̌Ăяo���@�N������x�����Ăяo��
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
			update();//�X�V�����̌Ăяo��
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
//�������֐��@�����A�߂�l�Ȃ�
void init()
{

	init_back();
	//�v���C���[�̏�����
	init_player();
	//�e�̏�����
	init_player_shot();
	initEnemyShot();
	//�G�̏���������
	initEnemy();
}

//�X�V�֐�
void update()
{
	//�v���C���[�̍X�V
	up_player();
	//�e�̍X�V
	up_player_shot();
	updateEnemyShot();
	//�G�̍X�V
	updateEnemy();
	//�`�揈��
	draw();
	updateGame();

	DrawFormatString(0, 0, GetColor(255, 255, 0), "���Ԍo�� %d �b", time);
	DrawFormatString(0, 24, GetColor(255, 255, 0), "��e %d ��", gameOverFlag);
	//DrawFormatString(400, 48, GetColor(255, 255, 0), "�X�R�A %d", score);
}

//�`�揈��
void draw()
{
	//�e�̕`��
	draw_player_shot();
	drawEnemyShot();
	//�G�̕`��
	drawEnemy();
	//�v���C���[�̕`��
	draw_player();
}