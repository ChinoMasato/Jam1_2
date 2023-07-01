#include "_system.h"
#include "DxLib.h"
#include <math.h>
#include "shot.h"
#include "enemyshot.h"
#include "enemy.h"
#include "player.h"
//#include "game.h"
//#include "effect.h"

extern bool gameOverFlag;//�Q�[���I�[�o�[����
extern int stage;
extern int i;
extern double speed;
extern double dx;
extern double dy;
extern double d;
extern int boss_defeat_num;
extern int start;
extern const int enemy_num;
extern int zenmetu;
extern int count;
extern int q;
extern int score;
extern int result;
extern int boss_action;
extern int j;
extern int action;
extern int one_second;

Object enemy[enemy_num];//�G
//�G�̏�����
void initEnemy()
{
	//�G�摜�̓ǂݍ���
	enemyimg = LoadGraph("enemy_1_1.png");
	//�G�̏���������
	for (i = 0; i < 10; i++) {
		enemy[i].x = GetRand(799);
		enemy[i].y = 0 - i * 100;
		enemy[i].r = 20;
		enemy[i].color = GetColor(255, 0, 0);
		enemy[i].fill = true;
		enemy[i].vx = 0.0;//x�̈ړ���
		enemy[i].vy = 2.0;//y�̈ړ���
		enemy[i].enable = true;

		enemy[i].hp = 1;
		enemy[i].enemytype = ENEMY1;
	}
	for (i = 10; i < 30; i++) {
		//double speed = 3.0;
		enemy[i].y = -1000 - i * 30;
		enemy[i].x = 200  * cos(enemy[i].y);
		enemy[i].r = 15;
		enemy[i].color = GetColor(255, 0, 0);
		enemy[i].fill = true;
		enemy[i].vx = 3.0;//x�̈ړ���
		enemy[i].vy = 3.0;//y�̈ړ���
		enemy[i].enable = true;

		enemy[i].hp = 1;
		enemy[i].enemytype = ENEMY2;
	}
}

//�^�������e������
void straightShot(int rad, Object ene)
{
	//�e�������ȂƂ��̂ݏ����l���Z�b�g���L���ɂ���
	for (int j = 0; j < EnemyShotNum; j++)
	{
		//���Ă�e���݂���
		if (enemyshot[j].enable == false) {
			//�e������
			enemyshot[j].x = ene.x;
			enemyshot[j].y = ene.y;
			double PI = 3.14159265358979323846264338;
			double minrad = PI / 180.0;//1�x�̃��W�A��
			double speed = 1.0;//���x
			enemyshot[j].vx = speed * cos(minrad * rad);
			enemyshot[j].vy = speed * sin(minrad * rad);
			enemyshot[j].enable = true;
			enemyshot[j].enemytype = ene.enemytype;
			enemyshot[j].vvx = enemyshot[j].vx * 0.01;
			enemyshot[j].vvy = enemyshot[j].vy * 0.01;
			break;
		}
	}
}

//���������֐�
//void explosion(Object ene)
//{
//	for (i = 0; i < EffectNum; i++)
//	{
//		if (effe[i].enable == false)
//		{
//			effe[i].enable = true;
//			effe[i].x = ene.x - 60;
//			effe[i].y = ene.y - 60;
//			effe[i].animeNo = 0;
//			break;
//		}
//	}
//}

//�G�̍X�V
void updateEnemy()
{
	for (int i = 0; i < enemy_num; i++) {
		if (enemy[i].enable == true) {
			//�G�������œ�����
			if (enemy[i].enemytype == ENEMY2)
			{
				enemy[i].vx = cos(enemy[i].vy);
			}
			enemy[i].x += enemy[i].vx;
			enemy[i].y += enemy[i].vy;
			if (enemy[i].x < 0 || enemy[i].x >= 800) {
				//�������[�E�E�[�ɏo����
				enemy[i].vx = enemy[i].vx * -1;
			}

			//�e�𔭎˂���
			if (canEnemyShot(enemy[i]))
			{
				if (enemy[i].enemytype == ENEMY1) {
					straightShot(180, enemy[i]);
					enemy[i].cooltime = one_second * 2;//�A�ˑ��x�@�������قǘA�˂ł���
				}
			}

			if (isHit(player, enemy[i]))
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
								explosion(enemy[i]);//����
							}
							gameOverFlag = true;//�Q�[���I�[�o�[�t���O�𗧂Ă�
						}
						else {
							player.muteki_time = one_second * 3; //60���t���[��*3=180��3�b�Ԗ��G���Ԃ��ł���
						}
					}
				}
			}

			for (int j = 0; j < ShotNum; j++) {
				//�G�ƒe�Ƃ̓����蔻��
				if (shot[j].enable == true) {
					if (isHit(shot[j], enemy[i]))
					{
						//�������Ă���
						if (enemy[i].hp > 0)
						{
							enemy[i].hp--;
						}
						if (enemy[i].hp <= 0)
						{
							if (enemy[i].enable == true)
							{
								PlaySoundFile("STG_enemy_defeat.mp3", DX_PLAYTYPE_BACK);
								explosion(enemy[i]);//����
							}
							enemy[i].enable = false;//�G�𖳌�
						}
						shot[j].enable = false;//�e�𖳌�
						break;
					}
				}
			}
			//�e���₷����
			if (enemy[i].cooltime > 0) {
				enemy[i].cooltime--;
			}
		}
	}
}

//�G�̕`��
void drawEnemy()
{
	for (int i = 0; i < enemy_num; i++) {
		if (enemy[i].enable == true) {
			DrawCircle(enemy[i].x, enemy[i].y, enemy[i].r, enemy[i].color, enemy[i].fill);
		}
	}
}
//�e�����Ă邩�m�F����֐�
bool canEnemyShot(Object enemy)
{
	//�e���₦�Ă���
	if (enemy.cooltime <= 0) {
		if(enemy.x >=0 &&
			enemy.x < 800 &&
			enemy.y>0 &&
			enemy.y < 600)
		{
			//��ʂ̒��ɂ���
			return true;
		}
	}

	return false;
}