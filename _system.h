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
extern int bossimg;

enum EnemyType
{
	ENEMY1,//�^�����������āA�^�������e������
	ENEMY2,//����ŏo�����āA�g����`���Ȃ���ːi���Ă���
	ENEMY3,//�s�K���ɓ����āA�z�[�~���O�e������
	ENEMY4,//�~�`�ɒe������
	SHIP,//���
	CANON1,//��C1
	CANON2,//��C2
	CANON3,//��C3
	BOSS//�{�X
};

enum ShotType
{
	NORMAL,
	BOMB_MOVE,
	BOMB_EXPLOSION,
	BEAM_STANDBY,
	BEAM_LAUNCH
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
	int boss_cooltime_M;
	int boss_cooltime_S;
	int boss_cooltime_B;
	int standbytime_B;
	int launchtime_B;
};


/*-----------------------------------------------------------------------------------------------*/


enum SCENE
{
	scene1, scene2, scene3, scene4
};

enum PLshot
{
	type1, type2, type3
};

struct entity
{
	double x, y, r;
	double x1, x2, x3, x4, y1, y2, y3, y4;
	double vx, vy, vvx, vvy;

	int color;
	bool live;
	int time;
	int muteki_time;
	int hp;
};

struct SYSTEM
{
	int se_shot;
	int se_break;
	int se_clear;
	int count_skin;
	int count_scene;
};

const int sys_ = 10;

extern SCENE scene;
extern PLshot pl_shot_type;
extern SYSTEM sys[sys_];


/*----------------------------------------------------------------------------------------------*/


bool isHit(entity en1, Object en2);//�����蔻��֐�
bool isRight(Object shot, entity target);//�i�s�����̉E�ɂ��邩

//�ǂ������֐����킩��񂪈ꉞ���ꂽ
void RotVec(Object& shot, double r);

void updateGame();


void scene_1();
void scene_2();
void scene_3();
void scene_4();