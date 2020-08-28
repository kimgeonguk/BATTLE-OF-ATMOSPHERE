#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include <Windows.h>

#include "Main.h"
#include"Xinput.h"

class TITLE
{
public:

	INT m_climb_count = 0;

	VOID Title_Scene();

	TITLE();

	FLOAT m_title_ui_tu_start = 0.5f;
	FLOAT m_title_ui_tu_help = 0.0f;
	FLOAT m_title_ui_tu_exit = 0.0f;

	enum SCENE_PHASE
	{
		LOAD,
		PROCESSING,
		RELEASES
	};

private:

	enum SelectUI_ID
	{
		title_ui_start,
		title_ui_help,
		title_ui_exit,
	};

	Xinput* xinput[2];

	SelectUI_ID current_id = title_ui_start;
	SCENE nextscene = GAME_SCENE;

	BOOL bgm = false;

	//プロトタイプ宣言
	VOID Loading();
	VOID Process();
	VOID Release();

};

#endif