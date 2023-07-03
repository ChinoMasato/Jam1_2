#include "DxLib.h"
#include "player_shot.h"
#include "player.h"
#include "_system.h"

entity ps[ps_];
PLshot pl_shot_type = type1;

void init_player_shot()
{
	sys[0].se_shot = LoadSoundMem("pyu.mp3");

	for (int i = 0; i < ps_; i++)
	{
		ps[i].r = 1;

		ps[i].vy = 5.0;

		ps[i].live = false;
	}
}

void up_player_shot()
{
		if (pl_shot_type == type1)
		{
			shot_type1();
		}
}

void draw_player_shot()
{
	for (int i = 0; i < ps_; i = i++)
	{
		if (ps[i].live == true)
		{
			DrawCircle(ps[i].x, ps[i].y, ps[i].r, ps[i].color, ps[i].live);
		}
	}
}

void shot_type1()
{
	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && pl.time == 0)
	{
		for (int i = 0; i < ps_; i = i + 4)
		{
			if (ps[i].live == false)
			{
				PlaySoundMem(sys[0].se_shot, DX_PLAYTYPE_BACK);

				for (int j = 0; j < 4; j++)
				{
					ps[i + j].color = GetColor(0, 255, 0);

					if (j == 0)
					{
						ps[i + j].live = true;
						ps[i + j].x = pl.x + 10;
						ps[i + j].y = pl.y + 20;
					}

					if (j == 1)
					{
						ps[i + j].live = true;
						ps[i + j].x = pl.x + 14;
						ps[i + j].y = pl.y + 18;
					}

					if (j == 2)
					{
						ps[i + j].live = true;
						ps[i + j].x = pl.x + 35;
						ps[i + j].y = pl.y + 18;
					}

					if (j == 3)
					{
						ps[i + j].live = true;
						ps[i + j].x = pl.x + 39;
						ps[i + j].y = pl.y + 20;
					}

					pl.time = 10;
				}
				break;
			}
		}
	}

	for (int i = 0; i < ps_; i++)
	{
		if (ps[i].live == true)
		{
			ps[i].y = ps[i].y - ps[i].vy;

			if (ps[i].y < 0)
			{
				ps[i].live = false;
			}
		}
	}
}