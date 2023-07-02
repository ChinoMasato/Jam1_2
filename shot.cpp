//�v���C���[�̒e�𑀍삷��֐����������t�@�C��
#include "_system.h"
#include "DxLib.h"
#include "shot.h"
#include "enemy.h"
#include <math.h>

Object shot[ShotNum];//�e

//�e�̏�����
void initShot()
{
	for (int i = 0; i < ShotNum; i++) {
		shot[i].r = 5;
		shot[i].color = GetColor(0, 0, 255);
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
//�e�̕`��
void drawShot()
{
	for (int i = 0; i < ShotNum; i++) {
		if (shot[i].enable == true)
		{
			if (shot[i].shottype == NORMAL)
			{
				//���@�e(�ʏ�)�̉摜
				DrawCircle(shot[i].x, shot[i].y, shot[i].r, shot[i].color, shot[i].fill);
			}
			if (shot[i].shottype == BOMB_MOVE)
			{
				//���@�e(�{��)�̉摜
				for (int j = 0; j < enemy_num; j++) 
				{
					if (shot[i].bombtime <= 60 && shot[i].bombtime > 0 && isHit(shot[i], enemy[j]) == false)
					{
						shot[i].r = 5;
						DrawCircle(shot[i].x, shot[i].y, shot[i].r, shot[i].color, shot[i].fill);
					}
					if (shot[i].bombtime <= 0 || isHit(shot[i], enemy[j]) == true)
					{
						shot[i].shottype = BOMB_EXPLOSION;
						shot[i].bomb_x = shot[i].x;
						shot[i].bomb_y = shot[i].y;
						shot[i].r = 5;
					}
				}
			}
			if (shot[i].shottype == BOMB_EXPLOSION)
			{
				DrawCircle(shot[i].bomb_x, shot[i].bomb_y, shot[i].r, shot[i].color, shot[i].fill);
				shot[i].r += 50;
				if (shot[i].r >= 150)
				{
					shot[i].r = 5;
					shot[i].enable = false;
				}
			}
			if (shot[i].shottype == BEAM_STANDBY)
			{
				//���@�e(�r�[��)�̉摜
			}
		}
	}
}