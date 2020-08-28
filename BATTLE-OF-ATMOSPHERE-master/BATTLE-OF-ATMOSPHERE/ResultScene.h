#ifndef RESULT_SCENE_H
#define RESULT_SCENE_H

#include <Windows.h>

#include"Xinput.h"

class RESULT
{
public:

	RESULT();

	VOID Result_Scene();

	enum SCENE_PHASE
	{
		LOAD,
		PROCESSING,
		RELEASES
	};

	//リザルトのフェーズの宣言
	RESULT::SCENE_PHASE phase = RESULT::LOAD;

private:

	Xinput* xinput[2];

	VOID Loading();
	VOID Process();
	VOID Release();

	FLOAT m_result_ui_tu_a = 0.5f;
	FLOAT m_result_ui_tu_b = 0.0f;
	FLOAT m_result_ui_tu_c = 0.0f;

	enum Result_SelectUI_ID
	{
		select_ui_retry,
		select_ui_title,

	};

	Result_SelectUI_ID Result_ID;


};
#endif
