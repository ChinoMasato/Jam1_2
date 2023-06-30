#pragma once
//struct �� enum �̋L���ꏊ
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
	double rad = 0;
	int hp;
	int muteki_time = 0;
	int aim_time = 0;
	int action;
};