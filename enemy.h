#pragma once
#include "en.h"
extern En enemy[20];//�G

void initEnemy();//�G�̏�����
void updateEnemy();//�G�̍X�V
void drawEnemy();//�G�̕`��

bool canEnemyShot(En enemy);//�e�����Ă邩�m�F

void explosion(En ene); //���������֐�