#pragma once
#include "en.h"
const int EnemyNum = 50;//�G�̐�
extern En enemy[EnemyNum];//�G

void initEnemy();//�G�̏�����
void updateEnemy();//�G�̍X�V
void drawEnemy();//�G�̕`��

bool canEnemyShot(En enemy);//�e�����Ă邩�m�F

