#pragma once
//struct �� enum �̋L���ꏊ

extern int playerimg;//�v���C���[�摜
//extern int shot_normalimg;//�e�摜

extern int enemyimg;//�G�摜
extern int shipimg;//��͉摜
extern int canon_1_leftimg;
extern int canon_1_rightimg;
extern int canon_2_leftimg;
extern int canon_2_rightimg;
extern int canon_3_left_upimg;
extern int canon_3_right_upimg;
extern int canon_3_left_downimg;
extern int canon_3_right_downimg;

enum EnemyType
{
	ENEMY1,//�^�����������āA�^�������e������
	ENEMY2,//����ŏo�����āA�g����`���Ȃ���ːi���Ă���
	ENEMY3,//�s�K���ɓ����āA�z�[�~���O�e������
	SHIP,//���
	CANON1,//��C1
	CANON2,//��C2
	CANON3//��C3
};

enum ShotType
{
	NORMAL,
	BOMB_MOVE,
	BOMB_EXPLOSION,
	BEAM
};

enum Place
{
	LEFT_UP,
	LEFT_DOWN,
	RIGHT_UP,
	RIGHT_DOWN
};

//�~�̍\����
struct Object
{
	EnemyType enemytype;//�G�̎��
	ShotType enemyshottype;
	Place place;//�C��̈ʒu
	ShotType shottype;
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
	int bomb_x;
	int bomb_y;
};

bool isHit(Object en1, Object en2);//�����蔻��֐�
bool isRight(Object shot, Object target);//�i�s�����̉E�ɂ��邩

//�ǂ������֐����킩��񂪈ꉞ���ꂽ
void RotVec(Object& shot, double r);

void updateGame();