#pragma once
#include "en.h"

enum ShotType
{
	NORMAL,
	BOMB,
	BEAM
};

const int ShotNum = 100;
extern En shot[ShotNum];//’e

void initShot();//’e‚Ì‰Šú‰»
void updateShot();//’e‚ÌXV
void drawShotNormal();
void drawShotBomb();