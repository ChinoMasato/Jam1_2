#pragma once
#include "_system.h"
const int enemy_num = 60;
extern Object enemy[enemy_num];//�G

void initEnemy();//�G�̏�����
void updateEnemy();//�G�̍X�V
void drawEnemy();//�G�̕`��

bool canEnemyShot(Object enemy);//�e�����Ă邩�m�F

void explosion(Object ene); //���������֐�