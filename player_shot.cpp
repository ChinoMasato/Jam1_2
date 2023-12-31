#include "DxLib.h"
#include "player_shot.h"
#include "player.h"
#include "_system.h"

entity ps[ps_];
PLshot pl_shot_type = type1;
extern int one_second;

void init_player_shot()
{
	sys[0].se_shot = LoadSoundMem("pyu.mp3");
	sys[1].se_shot = LoadSoundMem("ビームライフル.mp3"); 

	for (int i = 0; i < ps_; i++)
	{
		ps[i].r = 2;

		ps[i].vy = 5.0;

		ps[i].color = GetColor(255, 255 , 255);
		ps[i].live = false;
	}

	sys[0].count_shot = 0;
	sys[1].count_shot = 0;
	sys[2].count_shot = 0;
	sys[3].count_shot = 0;
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

		if (sys[0].count_shot >= one_second * 5)
		{
			DrawCircle(ps[i].x, ps[i].y, ps[i].r, ps[i].color, ps[i].live);
		}
	}
}

void shot_type1()
{
	for (int i = 0; i < ps_; i++)
	{
		if (ps[i].live == false)
		{
			ps[i].r = 2;
		}
	}

	if (CheckHitKey(KEY_INPUT_SPACE) == 1 && sys[3].count_shot == 0)
	{
		sys[0].count_shot++;
		sys[1].count_shot = 1;
	}

	if (CheckHitKey(KEY_INPUT_SPACE) == 0 && sys[1].count_shot == 1)
	{
		sys[3].count_shot = 1;
	}

	if (sys[0].count_shot < one_second * 5 && sys[3].count_shot == 1)
	{
		sys[0].count_shot = 0;

		for (int i = 0; i < ps_; i = i + 4)
		{
			if (ps[i].live == false)
			{
				PlaySoundMem(sys[0].se_shot, DX_PLAYTYPE_BACK);

				for (int j = 0; j < 4; j++)
				{

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
				}
				sys[0].count_shot = 0;
				sys[1].count_shot = 0;
				sys[3].count_shot = 0;
				break;
			}
		}
	}

	if (sys[0].count_shot >= one_second * 5 && pl.time == 0 && sys[3].count_shot == 1)
	{
		sys[2].count_shot++;

		if (sys[2].count_shot == 1)
		{
			PlaySoundMem(sys[1].se_shot, DX_PLAYTYPE_BACK);
		}

		for (int i = 0; i < ps_; i++)
		{
			if (ps[i].live == false)
			{

				int j = i % 4;
				ps[i].live = true;

				if (j == 0)
				{
					ps[i].x = pl.x + 10;
					ps[i].y = pl.y + 20;
				}

				if (j == 1)
				{
					ps[i].x = pl.x + 14;
					ps[i].y = pl.y + 18;
				}

				if (j == 2)
				{
					ps[i].x = pl.x + 35;
					ps[i].y = pl.y + 18;
				}

				if (j == 3)
				{
					ps[i].x = pl.x + 39;
					ps[i].y = pl.y + 20;
				}

				for (int k = 0; k < ps_; k++)
				{
					if (ps[k].live = true)
					{
						ps[k].r = 20;
						ps[k].y = ps[k].y - 9;;
					}
				}
			}
		}
	}

	if (sys[0].count_shot >= one_second * 5)
	{
		if (sys[2].count_shot >= one_second * 6)
		{
			sys[0].count_shot = 0;
			sys[1].count_shot = 0;
			sys[2].count_shot = 0;
			sys[3].count_shot = 0;
		}
	}


	for (int i = 0; i < ps_; i++)
	{
		if (ps[i].live == true)
		{
			if (sys[0].count_shot < one_second * 5)
			{
				ps[i].y = ps[i].y - ps[i].vy;

				if (ps[i].y < 0)
				{
					ps[i].live = false;
				}
			}

			if (sys[0].count_shot >= one_second * 5)
			{
				int j = i % 4;

				if (j == 0)
				{
					ps[i].x = pl.x + 10;
				}
				if (j == 1)
				{
					ps[i].x = pl.x + 14;
				}
				if (j == 2)
				{
					ps[i].x = pl.x + 35;
				}
				if (j == 3)
				{
					ps[i].x = pl.x + 39;
				}

				ps[i].y = ps[i].y -1;

				if (ps[i].y < 0)
				{
					ps[i].live = false;
				}

			}
		}
	}
}