#include "HelpScene.h"
#include <time.h>

HELP::HELP()
{
	xinput[0] = Xinput::GetInstance(Player::ONE);
	xinput[1] = Xinput::GetInstance(Player::TWO);
}

//リザルトのフェーズの移動
VOID HELP::Help_Scene()
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
VOID HELP::Loading()
{
	draw.LoadTexture("Help_1.png", HELP_BG);
	draw.LoadTexture("Help_2.png", HELP_BG2);
	phase = PROCESSING;
}
//リザルトの描画処理
VOID HELP::Process()
{
	

	//エンターでタイトルへ
	
	if (directx.KeyState[DIK_C] <= directx.PRESS||xinput[0]->IsKeyStrokePushed(CTRL::BUTTON_A)|| xinput[1]->IsKeyStrokePushed(CTRL::BUTTON_A))
	{
		m_scroll_move = TRUE;
	}

	if (m_scroll_move == TRUE)
	{
	
		m_scroll_x += m_scroll_speed;
	}

	if (m_scroll_x == 0)
	{
		m_scroll_move = FALSE;
	}

	if (m_scroll_x == 960) 
	{
		m_help_front = FALSE;
		m_scroll_speed = -30;
	}
	else if (m_scroll_x == -960)
	{
		m_help_front = TRUE;
		m_scroll_speed = 30;

	}

	if (m_help_front == TRUE) {
		draw.Draw(-m_scroll_x, -m_scroll_y, 0xffffffff, 0.0f, 0.0f, 1920, 1020, 1.0f, 1.0f, HELP_BG);
		draw.Draw(m_scroll_x, m_scroll_y, 0xffffffff, 0.0f, 0.0f, 1920, 1020, 1.0f, 1.0f, HELP_BG2);
	}
	else
	{
		draw.Draw(m_scroll_x, m_scroll_y, 0xffffffff, 0.0f, 0.0f, 1920, 1020, 1.0f, 1.0f, HELP_BG2);
		draw.Draw(-m_scroll_x, -m_scroll_y, 0xffffffff, 0.0f, 0.0f, 1920, 1020, 1.0f, 1.0f, HELP_BG);
	}
	
	


	if (directx.KeyState[DIK_RETURN] == directx.PRESS || xinput[0]->IsKeyStrokePushed(CTRL::BUTTON_B) || xinput[1]->IsKeyStrokePushed(CTRL::BUTTON_B))
	{
		phase = RELEASES;
	}
}
//リザルトのテクスチャの解放
VOID HELP::Release()
{
	for (INT i = 0; i < TEX_MAX; i++)
	{
		if (directx.pTexture[i] != nullptr)
		{
			directx.pTexture[i]->Release();
			directx.pTexture[i] = nullptr;
		}
	}
	phase = LOAD;
	scene = TITLE_SCENE;
}