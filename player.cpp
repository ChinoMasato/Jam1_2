//�v���C���[�𑀍삷��֐����������t�@�C��
#include "_system.h"
#include "DxLib.h"
#include "shot.h"
#include "player.h"

Object player;//�v���C���[
int shotse;//�V���b�gSE
double PI = 3.14;
int pushtime = 0;
int count = 0;

//�v���C���[�̏�����
void initPlayer()
{
	//�v���C���[�摜�̓ǂݍ���
	playerimg = LoadGraph("player_1.png");
	shotse = LoadSoundMem("maou_se_battle16.mp3");
	player.x = 400;
	player.y = 550;
	player.r = 10;
	player.color = GetColor(255, 255, 255);
	player.fill = true;
	player.cooltime = 0;
	player.vx = 3;
	player.vy = 3;

	player.hp = 5;
	player.muteki_time = 0;
}

//�v���C���[�̍X�V
void updatePlayer()
{
	count++;
	//�v���C���[�𓮂���
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		player.x += 2.0;
	}
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
	{
		player.x -= 2.0;
	}
	if (CheckHitKey(KEY_INPUT_UP) == 1)
	{
		player.y -= 2.0;
	}
	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
	{
		player.y += 2.0;
	}
	if (player.x < 0) {
		//�������[�ɏo����
		player.x = 0;
	}
	if (player.x > 800) {
		//�����E�[�ɏo����
		player.x = 800;
	}
	if (player.y < 0) {
		//�������[�ɏo����
		player.y = 0;
	}
	if (player.y > 600) {
		//�����E�[�ɏo����
		player.y = 600;
	}

	//�e��������(�ʏ�)
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 &&
		player.cooltime <= 0)
	{
		//�e�������ȂƂ��̂ݏ����l���Z�b�g���L���ɂ���
		for (int i = 0; i < ShotNum; i++)
		{
			//���Ă�e���݂���
			if (shot[i].enable == false) {
				//�e������
				shot[i].x = player.x;
				shot[i].y = player.y;
				shot[i].enable = true;
				player.cooltime = 10;//�A�ˑ��x�@�������قǘA�˂ł���
				shot[i].rad = 90.0 * PI / 180;
				shot[i].type = NORMAL;
				PlaySoundMem(shotse, DX_PLAYTYPE_BACK);
				drawShot();
				break;
			}
		}
	}
	//�e���₷����
	if (player.cooltime > 0) {
		player.cooltime--;
	}

	//�{������
	if (CheckHitKey(KEY_INPUT_B) == 1 &&
		player.cooltime_B <= 0)
	{
		//�e�������ȂƂ��̂ݏ����l���Z�b�g���L���ɂ���
		for (int i = 0; i < ShotNum; i++)
		{
			//���Ă�e���݂���
			if (shot[i].enable == false) {
				//�e������
				shot[i].x = player.x;
				shot[i].y = player.y;
				shot[i].enable = true;
				player.cooltime_B = 60;//�A�ˑ��x�@�������قǘA�˂ł���
				shot[i].rad = 270.0 * PI / 180;
				shot[i].type = BOMB;
				shot[i].bombtime = 60;
				PlaySoundMem(shotse, DX_PLAYTYPE_BACK);
				drawShot();
				break;
			}
		}
	}
	//�e���₷����(�{��)
	if (player.cooltime_B > 0) {
		player.cooltime_B--;
	}
	for (int i = 0; i < ShotNum; i++)
	{
		//�{������������܂ŃJ�E���g�_�E������
		if (shot[i].bombtime > 0)
		{
			shot[i].bombtime--;
		}
		// 1/2�b��ɔ������ďI���܂ł����1/2�b
		if (shot[i].bombtime <= 30)
		{
			
		}
	}
}

//�v���C���[�̕`��
void drawPlayer()
{
	if (player.muteki_time <= 0)
	{
		DrawGraph(player.x - 29, player.y - 24, playerimg, true);
	}
	if (player.muteki_time > 0 && count % 10 == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			DrawGraph(player.x - 29, player.y - 24, playerimg, true);
		}
	}
}