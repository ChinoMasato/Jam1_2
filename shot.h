#pragma once
#include "en.h"

enum ShotType
{
	NORMAL,
	BOMB,
	BEAM
};

const int ShotNum = 100;
extern En shot[ShotNum];//�e

void initShot();//�e�̏�����
void updateShot();//�e�̍X�V
void drawShotNormal();
void drawShotBomb();