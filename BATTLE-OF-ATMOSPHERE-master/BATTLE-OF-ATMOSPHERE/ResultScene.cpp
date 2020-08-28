#include "ResultScene.h"

#include "Main.h"
#include"GameScene.h"

extern WINNER winner;

RESULT::RESULT()
{
	xinput[0] = Xinput::GetInstance(Player::ONE);
	xinput[1] = Xinput::GetInstance(Player::TWO);
}

//リザルトのフェーズの移動
VOID RESULT::Result_Scene()
{

	switch (phase)
	{
	case LOAD:
		Loading();
		break;
	case PROCESSING:
		Process();
		break;
	case RELEASES:
		Release();
		phase = LOAD;
		break;
	}
}

//リザルトのテクスチャの読み込み
VOID RESULT::Loading()
{
	draw.LoadTexture("result_bg.jpg", RESULT_BG);
	draw.LoadTexture("result_logo.png", RESULT_LOGO);
	draw.LoadTexture("result_ui.png", RESULT_UI);



	phase = PROCESSING;
}

//リザルトの描画処理
VOID RESULT::Process()
{
	//ここでどちらが勝利したかを表示
	if (winner.m_is_one_win == TRUE)
	{
		draw.Draw(0, 0, 0xffffffff, 0.0f, 0.0f, 1920, 1080, 1.0f, 1.0f, RESULT_BG);
		draw.Draw(600, 190, 0xffffffff, 0.0f, 0.0f, 700, 700, 1.0f, 0.5f, RESULT_LOGO);
		draw.Draw(1450, 300, 0xffffffff, m_result_ui_tu_a, 0.0f, 370, 170, 0.5f, 0.25f, RESULT_UI);
		draw.Draw(1450, 650, 0xffffffff, m_result_ui_tu_c, 0.25f, 370, 170, 0.5f, 0.25f, RESULT_UI);
	}
	else if (winner.m_is_two_win == TRUE)
	{
		draw.Draw(0, 0, 0xffffffff, 0.0f, 0.0f, 1920, 1080, 1.0f, 1.0f, RESULT_BG);
		draw.Draw(600, 190, 0xffffffff, 0.0f, 0.5f, 700, 700, 1.0f, 0.5f, RESULT_LOGO);
		draw.Draw(1450, 300, 0xffffffff, m_result_ui_tu_a, 0.0f, 370, 170, 0.5f, 0.25f, RESULT_UI);
		draw.Draw(1450, 650, 0xffffffff, m_result_ui_tu_c, 0.25f, 370, 170, 0.5f, 0.25f, RESULT_UI);

	}
	else 
	{
		draw.Draw(0, 0, 0xffffffff, 0.0f, 0.0f, 1920, 1080, 1.0f, 1.0f, RESULT_BG);
		draw.Draw(1450, 300, 0xffffffff, m_result_ui_tu_a, 0.0f, 370, 170, 0.5f, 0.25f, RESULT_UI);
		draw.Draw(1450, 650, 0xffffffff, m_result_ui_tu_c, 0.25f, 370, 170, 0.5f, 0.25f, RESULT_UI);
	}


	if (directx.KeyState[DIK_DOWN] == directx.PRESS || xinput[0]->IsKeyStrokePushed(CTRL::LTHUMB_DOWN) || xinput[1]->IsKeyStrokePushed(CTRL::LTHUMB_DOWN))
	{
		switch (Result_ID)
		{
			m_result_ui_tu_a = 0.0f;
			m_result_ui_tu_b = 0.0f;
			m_result_ui_tu_c = 0.0f;

		case select_ui_retry:
			Result_ID = select_ui_title;
			m_result_ui_tu_c = 0.5f;
			m_result_ui_tu_a = 0.0f;
			break;
		default:
			break;
		}
	}
	if (directx.KeyState[DIK_UP] == directx.PRESS || xinput[0]->IsKeyStrokePushed(CTRL::LTHUMB_UP) || xinput[1]->IsKeyStrokePushed(CTRL::LTHUMB_UP))
	{
		switch (Result_ID)
		{
		case select_ui_title:
			Result_ID = select_ui_retry;
			m_result_ui_tu_a = 0.5f;
			m_result_ui_tu_c -= 0.5f;
			break;
		default:
			break;
		}
	}

	if (directx.KeyState[DIK_RETURN] == directx.PRESS || xinput[0]->IsKeyStrokePushed(CTRL::BUTTON_A) || xinput[1]->IsKeyStrokePushed(CTRL::BUTTON_A))
	{
		switch (Result_ID)
		{
		case select_ui_title:
			scene = TITLE_SCENE;
			break;
		case select_ui_retry:
			scene = GAME_SCENE;
		default:
			break;
		}

		phase = RELEASES;
	}
}


//リザルトのテクスチャの解放
VOID RESULT::Release()
{
	for (INT i = 0; i < TEX_MAX; i++)
	{
		if (directx.pTexture[i] != nullptr)
		{
			directx.pTexture[i]->Release();
			directx.pTexture[i] = nullptr;
		}
	}
	scene = TITLE_SCENE;
}

