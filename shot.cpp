//�v���C���[�̒e�𑀍삷��֐����������t�@�C��
#include "_system.h"
#include "DxLib.h"
#include "shot.h"

Object shot[ShotNum];//�e
//�e�̏�����
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
//�e�̍X�V
void updateShot()
{
	//�e���L���ȂƂ��ɒe�𓮂���
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
//�e�̕`��(�ʏ�)
void drawShotNormal()
{
	for (int i = 0; i < ShotNum; i++) {
		if (shot[i].enable == true)
		{
			//�e(�ʏ�)�̉摜

		}
	}
}
//�e�̕`��(�{��)
void drawShotBomb()
{
	for (int i = 0; i < ShotNum; i++) {
		if (shot[i].enable == true)
		{
			//�e(�{��)�̉摜

		}
	}
}