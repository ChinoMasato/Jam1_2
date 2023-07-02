#include "DxLib.h"
#include "backscreen.h"

entity cosmo[4];
entity dock[5];

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

	for (int i = 0; i < 5; i++)
	{
		dock[i].x = 0;
		dock[0].y = 0;
		dock[1].y = 200;
		dock[2].y = 0;
		dock[3].y = 0;
		dock[4].y = 0;

		dock[0].color = LoadGraph("dock_1.png");
		dock[1].color = LoadGraph("dock_2.png");
		dock[2].color = LoadGraph("dock_3.png");
		dock[3].color = LoadGraph("dock_4.png");
		dock[4].color = LoadGraph("dock_5.png");

		dock[0].x1 = 470, dock[0].x2 = 450, dock[0].x3 = 450;
		dock[0].y1 = 490, dock[0].y2 = 480, dock[0].y3 = 500;

	}

	sys[0].count_scene = 1;
	sys[1].count_scene = 0;
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

