#include "_system.h"
#include "DxLib.h"
#include <math.h>
#include "player.h"

int playerimg;//�v���C���[�摜
int enemyimg;//�G�摜
//int shot_normalimg;//�e�摜
int shipimg;
int canon_1_leftimg;
int canon_1_rightimg;
int canon_2_leftimg;
int canon_2_rightimg;
int canon_3_left_upimg;
int canon_3_right_upimg;
int canon_3_left_downimg;
int canon_3_right_downimg;
int bossimg;

int count = 0;
int one_second = 120;
int time = 0;
bool gameOverFlag;

void updateGame()
{
	count++;
	if (gameOverFlag == false && count % one_second == 0) //144��1�b�H(�w�Z��PC�̏ꍇ)
	{
		time++;
	}
	if (player.muteki_time > 0)
	{
		player.muteki_time--;
	}
}

//�~�̓����蔻��֐�
bool isHit(Object en1, Object en2)
{
	//��̉~�̓����蔻��
	double dx = en1.x - en2.x;//���̋���
	double dy = en1.y - en2.y;//�c�̋���
	double r2 = en1.r + en2.r;//���a�̍��Z

	if (dx* dx + dy * dy < r2 * r2)
	{
		//�������Ă���
		return true;
	}
	return false;
}

//�i�s�����̉E���Ƀ^�[�Q�b�g�����邩���肷��֐�
bool isRight(Object shot, Object target)
{
	double dy = target.y - shot.y;
	double dx = target.x - shot.x;
	double cross = shot.vx * dy - shot.vy * dx;

	return cross > 0;
}

//�ǂ������֐����킩��񂪈ꉞ���ꂽ
void RotVec(Object& shot, double r)
{
	double rot = r * (3.1415926539 / 180.0f);

	double rx = cos(rot) * shot.vx - sin(rot) * shot.vy;
	double ry = sin(rot) * shot.vx + cos(rot) * shot.vy;

	shot.vx = rx;
	shot.vy = ry;
}