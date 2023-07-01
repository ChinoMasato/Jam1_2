#pragma once
#include "_system.h"
const int enemy_num = 60;
extern Object enemy[enemy_num];//“G

void initEnemy();//“G‚Ì‰Šú‰»
void updateEnemy();//“G‚ÌXV
void drawEnemy();//“G‚Ì•`‰æ

bool canEnemyShot(Object enemy);//’e‚ªŒ‚‚Ä‚é‚©Šm”F

void explosion(Object ene); //”š”­”­¶ŠÖ”