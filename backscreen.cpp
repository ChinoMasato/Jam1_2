#include "DxLib.h"
#include "backscreen.h"

entity cosmo[4];

void init_back()
{
	for (int i = 0; i < 4; i++)
	{
		cosmo[i].x = 0;
		cosmo[0].y = 0;
		cosmo[1].y = -600;
		cosmo[2].y = 0;
		cosmo[3].y = -600;

		cosmo[0].vy = 1;
		cosmo[1].vy = 1;
		cosmo[2].vy = 2;
		cosmo[3].vy = 2;

		cosmo[0].color = LoadGraph("cosmo_1.png");
		cosmo[1].color = LoadGraph("cosmo_2.png");
		cosmo[2].color = LoadGraph("cosmo_3.png");
		cosmo[3].color = LoadGraph("cosmo_3.png");
	}
}

void up_back()
{
	for (int i = 0; i < 4; i++)
	{
		cosmo[i].y = cosmo[i].y + cosmo[i].vy;

		if (cosmo[i].y >= 600)
		{
			cosmo[i].y = -600;
		}
	}
}

void draw_back()
{
	for (int i = 0; i < 4; i++)
	{
		DrawGraph(cosmo[i].x, cosmo[i].y, cosmo[i].color, true);
	}
}