#include "TitleScene.h"

//タイトルのフェーズの宣言
TITLE::SCENE_PHASE phase = TITLE::LOAD;
//
//MapchipLoading Mp;
//DrawMap map;

TITLE::TITLE()
{
	Xinput::Create(2);

	xinput[0] = Xinput::GetInstance(Player::ONE);
	xinput[1] = Xinput::GetInstance(Player::TWO);
}

//タイトルのフェーズの移動
VOID TITLE::Title_Scene()
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

//タイトルのテクスチャの読み込み
VOID TITLE::Loading()
{


	soundsManager.AddFile(_T("タイトル画面候補１.mp3"), _T("TitleBGM"));
	bgm = soundsManager.Start(_T("TitleBGM"), true);
	soundsManager.SetVolume(_T("TitleBGM"), 100);


	draw.LoadTexture("title_bg.png", TITLE_BG);
	draw.LoadTexture("title_ui.png", TITLE_UI);
	draw.LoadTexture("title_logo.png", TITLE_LOGO);
	phase = PROCESSING;

	current_id = title_ui_start;
	nextscene = GAME_SCENE;
}

//タイトルの描画処理
VOID TITLE::Process()
{
	draw.Draw(0, 0, 0xffffffff, 0.0f, 0.0f, 1920, 1080, 1.0f, 1.0f, TITLE_BG);
	//タイトルUIの描画
	draw.Draw(580, 700, 0xffffffff, m_title_ui_tu_start, 0.0f, 300, 100, 0.5f, 0.25f, TITLE_UI);
	draw.Draw(580, 800, 0xffffffff, m_title_ui_tu_help, 0.25f, 300, 100, 0.5f, 0.25f, TITLE_UI);
	draw.Draw(580, 900, 0xffffffff, m_title_ui_tu_exit, 0.5f, 300, 100, 0.5f, 0.25f, TITLE_UI);

	draw.Draw(0, 100, 0xffffffff, 0.0f, 0.0f, 1250, 625, 1.0f, 1.0f, TITLE_LOGO);

	if (directx.KeyState[DIK_DOWN] == directx.PRESS||xinput[0]->IsKeyStrokePushed(CTRL::LTHUMB_DOWN))
	{
		if (m_climb_count == 0)
		{
			m_climb_count = 1;
		}

		if (m_climb_count == 2)
		{
			m_climb_count = 3;
		}
		
		// ボタンを押されたら選択UIをいったんリセット
		m_title_ui_tu_help = 0.0f;
		m_title_ui_tu_exit = 0.0f;
		m_title_ui_tu_start = 0.0f;

		//それぞれのUIがアニメーション、そのシーンへ遷移
		switch (current_id)
		{
		case title_ui_start:
			current_id = title_ui_help;
			m_title_ui_tu_help += 0.5f;
			nextscene = HELP_SCENE;
			break;
		case title_ui_help:
			current_id = title_ui_exit;
			m_title_ui_tu_exit += 0.5f;
			nextscene = EXIT_SCENE;
			break;
		case title_ui_exit:
			current_id = title_ui_exit;
			m_title_ui_tu_exit += 0.5f;
			nextscene = EXIT_SCENE;
			break;
		default:
			break;
		}
	}

	if (directx.KeyState[DIK_UP] == directx.PRESS|| xinput[0]->IsKeyStrokePushed(CTRL::LTHUMB_UP))
	{
		if (m_climb_count == 1)
		{
			m_climb_count = 2;
		}
		// ボタンを押されたら選択UIをいったんリセット
		m_title_ui_tu_help = 0.0f;
		m_title_ui_tu_exit = 0.0f;
		m_title_ui_tu_start = 0.0f;

		if (nextscene != CLIMB_SCENE)
		{
			//それぞれのUIがアニメーション、そのシーンへ遷移
			switch (current_id)
			{

			case title_ui_start:
				current_id = title_ui_start;
				m_title_ui_tu_start += 0.5f;
				nextscene = GAME_SCENE;
				break;
			case title_ui_help:
				current_id = title_ui_start;
				m_title_ui_tu_start += 0.5f;
				nextscene = GAME_SCENE;
				break;
			case title_ui_exit:
				current_id = title_ui_help;
				m_title_ui_tu_help += 0.5f;
				nextscene = HELP_SCENE;

				break;
			default:
				break;
			}
		}

	}

	if (directx.KeyState[DIK_RSHIFT] == directx.PRESS|| xinput[0]->IsKeyStrokePushed(CTRL::TRIGGER_RIGHT))
	{
		if (m_climb_count == 3)
		{
				scene = CLIMB_SCENE;
		}
	}

	//エンターでゲームへ
	if (directx.KeyState[DIK_RETURN] == directx.PRESS|| xinput[0]->IsKeyStrokePushed(CTRL::BUTTON_B))
	{
		m_title_ui_tu_start = 0.5f;
		m_title_ui_tu_help = 0.0f;
		m_title_ui_tu_exit = 0.0f;
		phase = RELEASES;

	}
}

//タイトルのテクスチャの解放
VOID TITLE::Release()
{
	soundsManager.Stop(_T("TitleBGM"));


	for (INT i = 0; i < TEX_MAX; i++)
	{
		if (directx.pTexture[i] != nullptr)
		{
			directx.pTexture[i]->Release();
			directx.pTexture[i] = nullptr;
		}
	}

	if (nextscene == GAME_SCENE)
	{
		scene = GAME_SCENE;
		m_climb_count = 0;
	}
	if (nextscene == HELP_SCENE)
	{
		scene = HELP_SCENE;
	}
	if (nextscene == EXIT_SCENE)
	{
		PostQuitMessage(0);
	}

}
