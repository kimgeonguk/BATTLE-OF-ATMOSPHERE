#ifndef CLIMB_SCENE_H_
#define CLIMB_SCENE_H_

//スクロールのスピード
#define SCROLL_SPEED  -0.0015f

#include <Windows.h>

#include"Xinput.h"

typedef struct
{
	INT m_cereate_max_count_one = 5;
	INT m_cereate_max_count_two = 5;
}CLIMBSTATE;

class CLIMB
{
public:

	CLIMBSTATE climb_state;

	CLIMB();

	VOID Climb_Scene();

	enum SCENE_PAHSE
	{
		LOAD,
		PROCESSING,
		RELEASES
	};

private:

	Xinput* xinput[2];

	FLOAT m_plus_scroll_speed = 0.5f;

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

	VOID Loading();
	VOID Process();
	VOID Release();

};

#endif