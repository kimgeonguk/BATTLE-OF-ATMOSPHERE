#ifndef GAME_SCENE_H
#define GAME_SCENE_H

//スクロールのスピード
#define SCROLL_SPEED  -0.001f

#include <Windows.h>

#include "Xinput.h"

typedef struct 
{
	BOOL m_is_one_win = FALSE;
	BOOL m_is_two_win = FALSE;
}WINNER;

class GAME
{
private:

	Xinput* xinput[2];

public:


	//スクロールの可視範囲
	FLOAT m_game_bg_tu = 0.25f;
	INT m_fc_background = 0;

	INT m_fc_count = 0;

	FLOAT m_count_tv = 0.0f;
	
	INT m_fc_finish = 0;
	INT m_finish_left_y = -600;
	INT m_finish_right_y = 1920;
	INT m_left_scr = 20;
	INT m_right_scr = 10;
	INT m_fc_right_finish_move = 0;
	INT m_fc_left_finish_move = 0;

	INT m_fc_cereate_one = 0;
	INT m_fc_cereate_two = 0;
	INT m_fc_ice_time_one = 0;
	INT m_fc_ice_time_two = 0;

	GAME();

	VOID Game_Scene();

	VOID Loading();
	VOID Process();
	VOID Release();

	BOOL bgm = false;
	INT sound_count = 0;

	enum SCENE_PAHSE
	{
		LOAD,
		PROCESSING,
		RELEASES
	};

};
#endif
