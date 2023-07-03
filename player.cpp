#include "DxLib.h"
#include "player.h"
#include "_system.h"

entity pl;
extern int count;

void init_player()
{
	sys[0].count_skin = LoadGraph("skin_1.png");
	sys[1].count_skin = LoadGraph("skin_2.png");
	sys[2].count_skin = LoadGraph("skin_3.png");

	pl.x = 375;
	pl.y = 480;

	pl.vx = 3.0;
	pl.vy = 3.0;

	pl.color = sys[0].count_skin;
	pl.live = true;
	pl.time = 0;
	pl.muteki_time = 0;
	pl.hp = 100;

	pl.r = 25;
}

void up_player()
{
	if (pl.live == true)
	{
		if (CheckHitKey(KEY_INPUT_W) == 1 && pl.y > 0)
		{
			pl.y = pl.y - pl.vy;
		}
		if (CheckHitKey(KEY_INPUT_S) == 1 && pl.y < 600 - 50)
		{
			pl.y = pl.y + pl.vy;
		}
		if (CheckHitKey(KEY_INPUT_A) == 1 && pl.x > 0)
		{
			pl.x = pl.x - pl.vx;
		}
		if (CheckHitKey(KEY_INPUT_D) == 1 && pl.x < 800 - 50)
		{
			pl.x = pl.x + pl.vx;
		}

		if (pl.time > 0)
		{
			pl.time--;
		}
	}
}

void draw_player()
{
	if (pl.muteki_time <= 0)
	{
		DrawGraph(pl.x, pl.y, pl.color, pl.live);
	}
	if (pl.muteki_time > 0 && count % 8 == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			DrawGraph(pl.x, pl.y, pl.color, pl.live);
		}
	}
}