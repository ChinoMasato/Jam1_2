#include "DxLib.h"
#include "player.h"
#include "backscreen.h"
#include "_system.h"

SCENE scene = scene1;

void scene_1()
{
	for (int i = 0; i < 5; i++)
	{
		DrawGraph(dock[i].x, dock[i].y, dock[i].color, true);
	}

	DrawFormatString(490, 483, GetColor(95, 95, 95), "ゲームスタート");
	DrawFormatString(490, 523, GetColor(95, 95, 95), "プレイヤースキン");

	if (CheckHitKey(KEY_INPUT_W) == 1)
	{
		sys[0].count_scene = 1;

		dock[0].y1 = dock[0].y1 - 40;
		dock[0].y2 = dock[0].y2 - 40;
		dock[0].y3 = dock[0].y3 - 40;

		if (dock[0].y1 <= 500)
		{
			dock[0].y1 = 490;
		}
		if (dock[0].y2 <= 500)
		{
			dock[0].y2 = 480;
		}
		if (dock[0].y3 <= 500)
		{
			dock[0].y3 = 500;
		}
	}

	if (CheckHitKey(KEY_INPUT_S) == 1)
	{

		sys[0].count_scene = 2;

		dock[0].y1 = dock[0].y1 + 40;
		dock[0].y2 = dock[0].y2 + 40;
		dock[0].y3 = dock[0].y3 + 40;

		if (dock[0].y1 >= 550)
		{
			dock[0].y1 = 530;
		}
		if (dock[0].y2 >= 550)
		{
			dock[0].y2 = 520;
		}
		if (dock[0].y3 >= 550)
		{
			dock[0].y3 = 540;
		}
	}

	DrawTriangle(dock[0].x1, dock[0].y1, dock[0].x2, dock[0].y2, dock[0].x3, dock[0].y3, GetColor(95, 95, 95), false);

	if (CheckHitKey(KEY_INPUT_SPACE) == 1)
	{
		if (sys[0].count_scene == 1)
		{
			PlayMusic("gagon.mp3", DX_PLAYTYPE_LOOP);
			sys[0].count_scene = 0;
			scene = scene2;
		}

		if (sys[0].count_scene == 2)
		{
			sys[0].count_scene = 0;
			dock[1].y = 80;
			scene = scene4;
		}
	}

}

void scene_2()
{
	if (sys[0].count_scene == 0)
	{
		DrawGraph(dock[0].x, dock[0].y, dock[0].color, true);
		DrawGraph(dock[1].x, dock[1].y, dock[1].color, true);
		DrawGraph(dock[2].x, dock[2].y, dock[2].color, true);
		DrawGraph(dock[3].x, dock[3].y, dock[3].color, true);
		DrawGraph(dock[4].x, dock[4].y, dock[4].color, true);

		PlaySoundFile("siren_3.mp3", DX_PLAYTYPE_BACK);
		sys[0].count_scene = 1;
	}

	if (sys[0].count_scene == 1)
	{
		DrawGraph(dock[0].x, dock[0].y, dock[0].color, true);
		DrawGraph(dock[1].x, dock[1].y, dock[1].color, true);
		DrawGraph(dock[2].x, dock[2].y, dock[2].color, true);
		DrawGraph(dock[3].x, dock[3].y, dock[3].color, true);
		DrawGraph(dock[4].x, dock[4].y, dock[4].color, true);
		dock[3].y = dock[3].y - 0.18;
		dock[2].y = dock[2].y + 0.2;
		if (dock[2].y >= 120)
		{
			StopSoundFile();
			PlaySoundFile("siren_2.mp3", DX_PLAYTYPE_BACK);
			sys[0].count_scene = 2;
		}
	}

	if (sys[0].count_scene == 2)
	{
		DrawGraph(dock[0].x, dock[0].y, dock[0].color, true);
		DrawGraph(dock[1].x, dock[1].y, dock[1].color, true);
		DrawGraph(pl.x, pl.y, pl.color, pl.live);
		DrawGraph(dock[2].x, dock[2].y, dock[2].color, true);
		DrawGraph(dock[3].x, dock[3].y, dock[3].color, true);
		DrawGraph(dock[4].x, dock[4].y, dock[4].color, true);

		pl.y = pl.y - 0.2;
		dock[1].y = dock[1].y - 0.2;
		if (dock[1].y <= 80)
		{
			StopMusic();
			StopSoundFile();
			PlaySoundFile("shot_RPG!.mp3", DX_PLAYTYPE_BACK);
			sys[0].count_scene = 3;
		}
	}

	if (sys[0].count_scene == 3)
	{
		DrawGraph(dock[0].x, dock[0].y, dock[0].color, true);
		DrawGraph(dock[1].x, dock[1].y, dock[1].color, true);
		DrawGraph(dock[2].x, dock[2].y, dock[2].color, true);
		DrawGraph(dock[3].x, dock[3].y, dock[3].color, true);
		DrawGraph(dock[4].x, dock[4].y, dock[4].color, true);
		DrawGraph(pl.x, pl.y, pl.color, pl.live);

		if (sys[1].count_scene == 0)
		{
			pl.vy = pl.vy * 1.05;
			if (pl.vy >= 10)
			{
				pl.vy = 10;
			}
			pl.y = pl.y - pl.vy;
		}

		if (sys[1].count_scene > 1)
		{
			pl.y = pl.y + pl.vy;
		}

		if (sys[1].count_scene == 0 && pl.y <= 50)
		{
			for (int i = 0; i < 5; i++)
			{
				dock[i].y = dock[i].y + 5;
			}

			if (sys[1].count_scene == 0 && pl.y <= -2000)
			{
				sys[1].count_scene = 1;
			}
		}

		if (sys[1].count_scene == 1)
		{
			pl.y = -100;
			pl.vy = 2.0;
			sys[1].count_scene = 2;
		}

		if (sys[1].count_scene == 2)
		{
			pl.vy = pl.vy * 0.995;
			if (pl.vy <= 0.1)
			{
				pl.vy = 3.0;
				PlayMusic("Disturbance.mp3", DX_PLAYTYPE_LOOP);
				scene = scene3;
			}
		}
	}
}

void scene_3()
{

}

void scene_4()
{
	DrawGraph(dock[0].x, dock[0].y, dock[0].color, true);
	DrawGraph(dock[1].x, dock[1].y, dock[1].color, true);
	DrawGraph(pl.x, pl.y, pl.color, pl.live);
	DrawGraph(dock[2].x, dock[2].y, dock[2].color, true);
	DrawGraph(dock[3].x, dock[3].y, dock[3].color, true);
	DrawGraph(dock[4].x, dock[4].y, dock[4].color, true);
	if (sys[0].count_scene == 0)
	{
		pl.y = 320;
		dock[3].y = dock[3].y - 1.8;
		dock[2].y = dock[2].y + 2.0;
		if (dock[2].y >= 120)
		{
			sys[0].count_scene = 1;
		}
	}
	if (sys[0].count_scene == 1)
	{
		DrawFormatString(490, 483, GetColor(95, 95, 95), "スキン変更 : 1 , 2 , 3");
		DrawFormatString(490, 523, GetColor(95, 95, 95), "決定 : W");
		if (CheckHitKey(KEY_INPUT_1) == 1)
		{
			pl.color = sys[0].count_skin;
		}
		if (CheckHitKey(KEY_INPUT_2) == 1)
		{
			pl.color = sys[1].count_skin;
		}
		if (CheckHitKey(KEY_INPUT_3) == 1)
		{
			pl.color = sys[2].count_skin;
		}

		if (CheckHitKey(KEY_INPUT_W) == 1)
		{
			sys[0].count_scene = 2;
		}
	}

	if (sys[0].count_scene == 2)
	{
		dock[3].y = dock[3].y + 1.8;
		dock[2].y = dock[2].y - 2.0;
		if (dock[2].y <= 0)
		{
			pl.y = 480;
			dock[1].y = 200;
			scene = scene1;
		}
	}
}