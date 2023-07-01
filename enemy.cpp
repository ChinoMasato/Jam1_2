#include "en.h"
#include "DxLib.h"
#include <math.h>
#include "shot.h"
#include "enemyshot.h"
#include "enemy.h"
#include "player.h"
#include "game.h"
#include "init.h"
#include "effect.h"

extern bool gameOverFlag;//�Q�[���I�[�o�[����
extern int stage;
extern int i;
extern double speed;
extern double dx;
extern double dy;
extern double d;
extern int boss_defeat_num;
extern int start;
extern int enemy_num;
extern int zenmetu;
extern int count;
extern int q;
extern int score;
extern int result;
extern int boss_action;
extern int j;
extern int action;
extern int one_second;
extern GameScene scene;

En enemy[20];//�G
//�G�̏�����
void initEnemy()
{
	//�G�摜�̓ǂݍ���
	enemyimg = LoadGraph("enemy_1_1.png");
	if (stage >= 1 && stage <= 2)
	{
		//�G�̏���������
		for (i = 0; i < 2 * stage; i++) { //��(�V���b�g�L��)
			enemy[i].x = GetRand(499) + 300;
			enemy[i].y = GetRand(599);
			enemy[i].r = GetRand(10) + 30;
			enemy[i].color = GetColor(255, 0, 0);
			enemy[i].fill = true;
			enemy[i].vx = 1.0;//x�̈ړ���
			enemy[i].vy = 1.0;//y�̈ړ���
			enemy[i].enable = true;

			enemy[i].hp = 3 + boss_defeat_num;
			enemy[i].type = ENEMY1;
		}
		for (i = 2 * stage; i < 6 * stage; i++) { //��
			enemy[i].x = GetRand(499) + 300;
			enemy[i].y = GetRand(599);
			enemy[i].r = GetRand(10) + 10;
			enemy[i].color = GetColor(0, 255, 0);
			enemy[i].fill = true;

			speed = 2.0;//���x
			dx = player.x - enemy[i].x;//�v���C���[�ƓG��x�����̋���
			dy = player.y - enemy[i].y;//�v���C���[�ƓG��y�����̋���
			d = sqrt(dx * dx + dy * dy);//�G�ƃv���C���[�Ƃ̋���
			enemy[i].vx = speed * (dx / d);//x�̈ړ���
			enemy[i].vy = speed * (dy / d);//y�̈ړ���
			enemy[i].enable = true;

			enemy[i].hp = 1 + boss_defeat_num;
		}
		for (i = 6 * stage; i < 8 * stage; i++) { //��
			enemy[i].x = GetRand(499) + 300;
			enemy[i].y = GetRand(599);
			enemy[i].r = GetRand(10) + 5;
			enemy[i].color = GetColor(0, 0, 255);
			enemy[i].fill = true;

			enemy[i].vx = 5;//x�̈ړ���
			enemy[i].vy = 5;//y�̈ړ���
			enemy[i].enable = true;

			enemy[i].hp = 1 + boss_defeat_num;
		}
		for (i = 8 * stage; i < 10 * stage; i++) { //��(�V���b�g�L��)
			enemy[i].x = GetRand(499) + 300;
			enemy[i].y = GetRand(599);
			enemy[i].r = GetRand(10) + 20;
			enemy[i].color = GetColor(167, 87, 168);
			enemy[i].fill = true;

			enemy[i].vx = 1.5;//x�̈ړ���
			enemy[i].vy = 1.5;//y�̈ړ���
			enemy[i].enable = true;

			enemy[i].hp = 2 + boss_defeat_num;
			enemy[i].type = ENEMY2;
		}
	}
	if (stage == 3)
	{
		//�{�X(��)
		i = 0;
		enemy[i].x = 700;
		enemy[i].y = GetRand(599);
		enemy[i].r = 50;
		enemy[i].color = GetColor(255, 0, 0);
		enemy[i].fill = true;
		enemy[i].vx = 0.0;//x�̈ړ���
		enemy[i].vy = 1.0;//y�̈ړ���
		enemy[i].enable = true;

		enemy[i].hp = 30 * (boss_defeat_num + 1);
		enemy[i].type = ENEMY3;

		//�{�X�̃t�@���l��(�e�͉��F�A�{�̂͐F)
		for (i = 1; i < 5 + boss_defeat_num; i++)
		{
			enemy[i].x = 600;
			enemy[i].y = GetRand(599);
			enemy[i].r = 15;
			enemy[i].color = GetColor(0, 0, 255);
			enemy[i].fill = true;
			enemy[i].vx = 3.0;//x�̈ړ���
			enemy[i].vy = 3.0;//y�̈ړ���
			enemy[i].enable = true;

			enemy[i].hp = 2 + boss_defeat_num;
			enemy[i].type = ENEMY2;
			enemy[i].action = GetRand(5);
		}
	}
}

//�^�������e������
void straightShot(int rad, En ene)
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
			enemyshot[j].type = ene.type;
			enemyshot[j].vvx = enemyshot[j].vx * 0.01;
			enemyshot[j].vvy = enemyshot[j].vy * 0.01;
			break;
		}
	}
}

//�_���Č���
void aimShot(En ene)
{
	//�e�����Ă���
//�e�������ȂƂ��̂ݏ����l���Z�b�g���L���ɂ���
	for (int j = 0; j < EnemyShotNum; j++)
	{
		//���Ă�e���݂���
		if (enemyshot[j].enable == false) {
			//�e������
			enemyshot[j].x = ene.x;
			enemyshot[j].y = ene.y;

			double speed = 1.0;//���x
			double dx = player.x - ene.x;//�v���C���[�ƓG��x�����̋���
			double dy = player.y - ene.y;//�v���C���[�ƓG��y�����̋���
			double d = sqrt(dx * dx + dy * dy);//�G�ƃv���C���[�Ƃ̋���
			enemyshot[j].vx = speed * (dx / d);//x�̈ړ���
			enemyshot[j].vy = speed * (dy / d);//y�̈ړ���
			enemyshot[j].enable = true;
			enemyshot[j].type = ene.type;
			enemyshot[j].vvx = enemyshot[j].vx * 0.01;
			enemyshot[j].vvy = enemyshot[j].vy * 0.01;
			enemyshot[j].aim_time = one_second * 2;
			break;
		}
	}
}

//2��Ō���
void twinShot(int rad, En ene, int q)
{
	//�e�������ȂƂ��̂ݏ����l���Z�b�g���L���ɂ���
	for (int j = 0; j < EnemyShotNum; j++)
	{
		//���Ă�e���݂���
		if (enemyshot[j].enable == false) {
			//�e������
			double PI = 3.14159265358979323846264338;
			double minrad = PI / 180.0;//1�x�̃��W�A��
			double speed = 3.0;//���x
			enemyshot[j].x = ene.x;
			enemyshot[j].y = ene.y - 15 + (q * 30);
			enemyshot[j].vx = speed * cos(minrad * rad);
			enemyshot[j].vy = speed * sin(minrad * rad);
			enemyshot[j].enable = true;
			break;
		}
	}
}

//���������֐�
void explosion(En ene)
{
	for (i = 0; i < EffectNum; i++)
	{
		if (effe[i].enable == false)
		{
			effe[i].enable = true;
			effe[i].x = ene.x - 60;
			effe[i].y = ene.y - 60;
			effe[i].animeNo = 0;
			break;
		}
	}
}

//�G�̍X�V
void updateEnemy()
{
	if (start == 0)
	{
		scene = Game;
		if (stage >= 1 && stage <= 2)
		{
			enemy_num = 10 * stage;
			for (int i = 0; i < enemy_num; i++) {
				if (enemy[i].enable == true) {
					//�G�������œ�����
					if (i >= 0 && i < 6 * stage) //�ǔ��^(�ΐF)�̓���
					{
						dx = player.x - enemy[i].x;//�v���C���[�ƓG��x�����̋���
						dy = player.y - enemy[i].y;//�v���C���[�ƓG��y�����̋���
						d = sqrt(dx * dx + dy * dy);//�G�ƃv���C���[�Ƃ̋���
						enemy[i].vx = speed * (dx / d);//x�̈ړ���
						enemy[i].vy = speed * (dy / d);//y�̈ړ���
					}
					if (i >= 8 * stage && i < 10 * stage) //�����_���^(���F)�̓���1
					{
						if (count % (one_second * 5) == 0)
						{
							enemy[i].action = GetRand(3);
						}
						if (enemy[i].action == 3)
						{
							enemy[i].vx = enemy[i].vx * -1;
						}
						if (enemy[i].action == 2)
						{
							enemy[i].vy = enemy[i].vy * -1;
						}
						if (enemy[i].action == 1)
						{
							enemy[i].vx = enemy[i].vx * -1;
							enemy[i].vy = enemy[i].vy * -1;
						}
					}
					enemy[i].x += enemy[i].vx;
					enemy[i].y += enemy[i].vy;

					if (enemy[i].x < 0 || enemy[i].x >= 800) {
						//�������[�E�E�[�ɏo����
						enemy[i].vx = enemy[i].vx * -1;
					}
					if (enemy[i].y < 0 || enemy[i].y >= 600) {
						//������[�E���[�ɏo����
						enemy[i].vy = enemy[i].vy * -1;
					}

					if (i >= 0 && i < 2 * stage || i >= 8 * stage && i < 10 * stage)
					{
						//�e�𔭎˂���
						if (canEnemyShot(enemy[i]))
						{
							if (enemy[i].type == ENEMY1) {
								straightShot(180, enemy[i]);
								enemy[i].cooltime = one_second * 2;//�A�ˑ��x�@�������قǘA�˂ł���
							}
							if (enemy[i].type == ENEMY2) {
								aimShot(enemy[i]);
								enemy[i].cooltime = one_second * 3;//�A�ˑ��x�@�������قǘA�˂ł���
							}
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
									if (gameOverFlag == false)
									{
										if (i >= 0 && i < 2 * stage) {
											score += 1;
										}
										if (i >= 2 * stage && i < 6 * stage) {
											score += 3;
										}
										if (i >= 6 * stage && i < 8 * stage) {
											score += 8;
										}
										if (i >= 8 * stage && i < 10 * stage) {
											score += 5;
										}
										zenmetu++;
									}
									
									if (zenmetu == enemy_num)
									{
										start = 1;
										count = 0;
										result = 1;
									}
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
		if (stage == 3)
		{
			enemy_num = 5 + boss_defeat_num;
			for (i = 0; i < enemy_num; i++)
			{
				if (enemy[i].enable == true)
				{
					if (i == 0) //�{�X�̓���
					{
						enemy[i].y += enemy[i].vy;
					}
					if (i >= 1 && i < enemy_num) //�t�@���l���̓���
					{
						if (count % (one_second * 5) == 0)
						{
							enemy[i].action = GetRand(3);
						}
						if (enemy[i].action == 3) //�{�X�t�@���l���̓���1-1(�ʏ�)
						{
							enemy[i].vx = enemy[i].vx * -1;
						}
						if (enemy[i].action == 2) //�{�X�t�@���l���̓���1-2(�ʏ�)
						{
							enemy[i].vy = enemy[i].vy * -1;
						}
						if (enemy[i].action == 1)
						{
							enemy[i].vx = enemy[i].vx * -1;
							enemy[i].vy = enemy[i].vy * -1;
						}
						enemy[i].x += enemy[i].vx;
						enemy[i].y += enemy[i].vy;
					}

					if (enemy[i].x < 0 || enemy[i].x >= 800) {
						//�������[�E�E�[�ɏo����
						enemy[i].vx = enemy[i].vx * -1;
					}
					if (enemy[i].y < 0 || enemy[i].y >= 600) {
						//������[�E���[�ɏo����
						enemy[i].vy = enemy[i].vy * -1;
					}

					//�e�𔭎˂���
					if (canEnemyShot(enemy[i]))
					{
						if (enemy[i].type == ENEMY3) {
							for (q = 0; q < 2; q++)
							{
								twinShot(180, enemy[i], q);
							}
							enemy[i].cooltime = one_second * 1;//�A�ˑ��x�@�������قǘA�˂ł���
						}
						if (enemy[i].type == ENEMY2) {
							aimShot(enemy[i]);
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
									if (gameOverFlag == false)
									{
										StopMusic();
										PlayMusic("STG_gameover.mp3", DX_PLAYTYPE_LOOP);
										PlaySoundFile("STG_enemy_defeat.mp3", DX_PLAYTYPE_BACK);
										explosion(enemy[i]);//����
									}
									player.color = enemyshot[i].color;
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
										if (enemy[i].type == ENEMY3)
										{
											PlaySoundFile("STG_boss_defeat.mp3", DX_PLAYTYPE_BACK);
										}
										if (enemy[i].type == ENEMY2)
										{
											PlaySoundFile("STG_enemy_defeat.mp3", DX_PLAYTYPE_BACK);
										}
										explosion(enemy[i]);//����
									}
									enemy[i].enable = false;//�G�𖳌�
									if (gameOverFlag == false)
									{
										if (enemy[i].type == ENEMY3)
										{
											zenmetu = enemy_num;
											score += 30 * (boss_defeat_num + 1);
										}
										if (enemy[i].type == ENEMY2)
										{
											score += 5;
										}
									}

									if (zenmetu == enemy_num)
									{
										for (q = 0; q < enemy_num; q++)
										{
											if (enemy[i].type == ENEMY2)
											{
												enemy[i].enable = false;//�G�𖳌�
											}
										}
										start = 1;
										count = 0;
										result = 1;
									}
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
	}
	
}

//�G�̕`��
void drawEnemy()
{
	if (start == 0)
	{
		for (int i = 0; i < enemy_num; i++) {
			if (enemy[i].enable == true) {
				DrawGraph(enemy[i].x - 24, enemy[i].y - 24, enemyimg, true);
				//DrawCircle(enemy[i].x, enemy[i].y, enemy[i].r, enemy[i].color, enemy[i].fill);
			}
		}
	}
}
//�e�����Ă邩�m�F����֐�
bool canEnemyShot(En enemy)
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