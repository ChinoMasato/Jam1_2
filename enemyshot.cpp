#include "_system.h"
#include "DxLib.h"
#include "enemyshot.h"
#include "player.h"
//#include "game.h"
#include <math.h>

extern int start;
extern bool gameOverFlag;
extern int stage;
extern double d;
extern double dx;
extern double dy;
extern double speed;
extern int one_second;
extern int count;

Object enemyshot[EnemyShotNum];//�e
//�e�̏�����
void initEnemyShot()
{
	for (int i = 0; i < EnemyShotNum; i++) {
		enemyshot[i].r = 5;
		enemyshot[i].color = GetColor(255,0, 0);
		enemyshot[i].fill = true;
		enemyshot[i].enable = false;
	}
}
//�e�̍X�V
void updateEnemyShot()
{
	//�e���L���ȂƂ��ɒe�𓮂���
	for (int i = 0; i < EnemyShotNum; i++)
	{
		if (enemyshot[i].enable == true) {
			//�e�̎�ނɉ����ē�������ς���
			if (enemyshot[i].enemytype == ENEMY1) {
				enemyshot[i].vx = enemyshot[i].vx + enemyshot[i].vvx;
				enemyshot[i].vy = enemyshot[i].vy + enemyshot[i].vvy;
			}
			if (enemyshot[i].enemytype == ENEMY3 && enemyshot[i].aim_time > 0) {
				if (isRight(enemyshot[i], player))
				{
					RotVec(enemyshot[i], 1);
				}
				else {
					RotVec(enemyshot[i], -1);
				}
				enemyshot[i].aim_time--;
			}
			if (enemyshot[i].enemytype == CANON1)
			{
				if (isRight(enemyshot[i], player))
				{
					RotVec(enemyshot[i], 1);
				}
				else {
					RotVec(enemyshot[i], -1);
				}
				enemyshot[i].aim_time--;
			}
			enemyshot[i].x = enemyshot[i].x + enemyshot[i].vx;
			enemyshot[i].y = enemyshot[i].y + enemyshot[i].vy;
			if (enemyshot[i].x >= 800 ||
				enemyshot[i].x < 0 ||
				enemyshot[i].y >= 600 ||
				enemyshot[i].y < 0)
			{
				enemyshot[i].enable = false;
			}
		}
		if (isHit(player, enemyshot[i]))
		{
			//�������Ă���
			if (player.muteki_time <= 0)
			{
				if (player.hp > 0)
				{
					player.hp--;
					PlaySoundFile("STG_player_damege.mp3", DX_PLAYTYPE_BACK);

					//�f�o�b�O�p
					//player.hp++;
					if (player.hp <= 0)
					{
						player.color = enemyshot[i].color;
						if (gameOverFlag == false)
						{
							StopMusic();
							PlayMusic("STG_gameover.mp3", DX_PLAYTYPE_LOOP);
							PlaySoundFile("STG_enemy_defeat.mp3", DX_PLAYTYPE_BACK);
						}
						gameOverFlag = true;//�Q�[���I�[�o�[�t���O�𗧂Ă�
					}
					else {
						player.muteki_time = one_second * 3; //3�b�Ԗ��G���Ԃ��ł���
					}
				}
			}
		}
	}
}
//�e�̕`��
void drawEnemyShot()
{
	for (int i = 0; i < EnemyShotNum; i++) {
		if (enemyshot[i].enable == true)
		{
			if (enemyshot[i].enemyshottype == NORMAL)
			{
				//���@�e(�ʏ�)�̉摜
				DrawCircle(enemyshot[i].x, enemyshot[i].y, enemyshot[i].r, enemyshot[i].color, enemyshot[i].fill);
			}
			if (enemyshot[i].enemyshottype == BOMB_MOVE)
			{
				//enemyshot[i].color = GetColor(255, 255, 0);
				//���@�e(�{��)�̉摜
				if (enemyshot[i].bombtime <= 120 && enemyshot[i].bombtime > 0 && isHit(enemyshot[i], player) == false)
				{
					enemyshot[i].r = 5;
					DrawCircle(enemyshot[i].x, enemyshot[i].y, enemyshot[i].r, enemyshot[i].color, enemyshot[i].fill);
				}
				if (enemyshot[i].bombtime <= 0 || isHit(enemyshot[i], player) == true)
				{
					enemyshot[i].enemyshottype = BOMB_EXPLOSION;
					enemyshot[i].bomb_x = enemyshot[i].x;
					enemyshot[i].bomb_y = enemyshot[i].y;
					enemyshot[i].r = 5;
				}
			}
			if (enemyshot[i].enemyshottype == BOMB_EXPLOSION)
			{
				DrawCircle(enemyshot[i].bomb_x, enemyshot[i].bomb_y, enemyshot[i].r, enemyshot[i].color, enemyshot[i].fill);
				enemyshot[i].r += 25;
				if (enemyshot[i].r >= 75)
				{
					enemyshot[i].r = 5;
					enemyshot[i].enable = false;
				}
			}
			if (enemyshot[i].enemyshottype == BEAM)
			{
				//���@�e(�r�[��)�̉摜
			}
		}
	}
}