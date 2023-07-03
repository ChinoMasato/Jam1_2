#pragma once
#include "_system.h"
const int enemy_num = 60;
extern Object enemy[enemy_num];//敵

void initEnemy();//敵の初期化
void updateEnemy();//敵の更新
void drawEnemy();//敵の描画

bool canEnemyShot(Object enemy);//弾が撃てるか確認

bool canBossShot_M(Object enemy);//弾が撃てるか確認
bool canBossShot_B(Object enemy);//弾が撃てるか確認
bool canBossShot_S(Object enemy);//弾が撃てるか確認


//void explosion(Object ene); //爆発発生関数