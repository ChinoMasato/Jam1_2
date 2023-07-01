#pragma once
//struct �� enum �̋L���ꏊ

extern int playerimg;//�v���C���[�摜
extern int enemyimg;//�G�摜
extern int shot_normalimg;//�e�摜

enum EnemyType
{
	ENEMY1,//�G�^�C�v�P
	ENEMY2,//�G�^�C�v�Q
	ENEMY3//�G�^�C�v3
};

enum ShotType
{
	NORMAL,
	BOMB,
	BEAM
};

//�~�̍\����
struct Object
{
	EnemyType type;//�G�̎��
	ShotType type;
	double x;//X���W
	double y;//Y���W
	double r;//���a
	int color;//�~�̐F
	bool fill;//�h��Ԃ����ۂ�
	double vx;//���̈ړ���
	double vy;//�c�̈ړ���
	double vvx;//���̈ړ��ʂ̑���
	double vvy;//�c�̈ړ��ʂ̑���
	bool enable;//�L���t���O�i�����Ă邩�A����ł邩�j
	int cooltime;//�A�˂ł��Ȃ��悤�ɂ���^�C�}�[
	int cooltime_B;//�A�˂ł��Ȃ��悤�ɂ���^�C�}�[(�{��ver)
	double rad = 0;
	int hp;
	int muteki_time = 0;//�v���C���[�̖��G����
	int aim_time = 0;//�z�[�~���O���鎞��(�����ƃz�[�~���O�����Ȃ�)
	int action;//�G�̍s���p�^�[���Ȃǂ�
	int bombtime;//�{���̔������I���܂ł̎���(1�b��z��)
};

bool isHit(Object en1, Object en2);//�����蔻��֐�
bool isRight(Object shot, Object target);//�i�s�����̉E�ɂ��邩

//�ǂ������֐����킩��񂪈ꉞ���ꂽ
void RotVec(Object& shot, double r);