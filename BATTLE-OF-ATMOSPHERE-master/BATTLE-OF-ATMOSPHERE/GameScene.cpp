#include "GameScene.h"

#include <stdlib.h>
#include <time.h>

#include "Main.h"
#include "Stage.h"
#include "Character.h"
#include "Collision.h"
#include "Create.h"
#include "Ice.h"
#include "Jet.h"

extern STAGE stage;
extern SPACEMAN spaceman;
extern COLLISION collision;
extern CREATE create;
extern JET jet;
extern ICE ice;

WINNER winner;

GAME::SCENE_PAHSE phase = GAME::LOAD;

GAME::GAME()
{
	Xinput::Create(2);

	xinput[0] = Xinput::GetInstance(Player::ONE);
	xinput[1] = Xinput::GetInstance(Player::TWO);
}

//ゲームのフェーズの移動
VOID GAME::Game_Scene()
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

//ゲームのテクスチャの読み込み
VOID GAME::Loading()
{

	soundsManager.AddFile(_T("メインゲーム画面候補１.mp3"), _T("GameBGM"));
	soundsManager.SetVolume(_T("GameBGM"), 100);

	soundsManager.AddFile(_T("ゲーム開始音.mp3"), _T("GameStart"));
	soundsManager.SetVolume(_T("GameStart"), 100);

	soundsManager.AddFile(_T("ゲーム終了音.mp3"), _T("GameEnd"));
	bgm = soundsManager.Start(_T("TitleBGM"), true);
	soundsManager.SetVolume(_T("GameEnd"), 100);

	draw.LoadTexture("game_bg.png", GAME_BG);
	draw.LoadTexture("spaceman_one.png", CHARCTER);
	draw.LoadTexture("spaceman_two.png", CHARCTER_TWO);
	draw.LoadTexture("block.png", GAME_STAGE);
	draw.LoadTexture("blast.png", BLAST);
	draw.LoadTexture("item.png",ITEM);
	draw.LoadTexture("finish.png", FINISH);
	draw.LoadTexture("321go.png",COUNTDOWN);

	stage.InitBlock();

	spaceman.SpaceManInit(&spaceman.char_one);
	spaceman.SpaceManInit(&spaceman.char_two);

	srand((unsigned int)time(NULL));

	phase = PROCESSING;
}

VOID GAME::Process()
{
	
		//ゲーム背景の描画
		draw.Draw(0, 0, 0xffffffff, 0.0f, m_game_bg_tu, 1920, 1080, 1.0f, 0.25f, GAME_BG);

		if (m_fc_count >= 245)
		{
			bgm = soundsManager.Start(_T("GameBGM"), true);


			//ブロックの描画
			for (INT i = 0; i < BLOCK_QUANTITY; i++)
			{
				stage.DrawBlock(stage.block[i]);
			}



		//どちらが勝利したか判断している
		if (spaceman.char_one.m_y > WINDOW_HEIGHT + (BLOCK_SIZE * 3))
		{
			if(sound_count == 0)soundsManager.Start(_T("GameEnd"), false);

			sound_count++;
			m_fc_finish++;
			m_fc_left_finish_move++;
			if (m_fc_finish <= 60 * 6)
			{
				draw.Draw(m_finish_left_y, 390, 0xffffffff, 0.0f, 0.0f, 600, 150, 1.0f, 0.5f, FINISH);
				draw.Draw(m_finish_right_y, 540, 0xffffffff, 0.0f, 0.5f, 600, 150, 1.0f, 0.5f, FINISH);
				//Finishの左の画像
				if (m_fc_left_finish_move >= 2)
				{
					m_finish_left_y += m_left_scr;
					m_fc_left_finish_move = 0;

					if (m_finish_left_y >= 660)
					{
						m_left_scr = 0;
					}
				}
				//Finishの右の画像
				if (m_fc_right_finish_move <= 2)
				{
					m_finish_right_y -= m_right_scr;
					m_fc_right_finish_move = 0;

					if (m_finish_right_y <= 660)
					{
						m_right_scr = 0;
					}
				}


				m_fc_background = 0;
			}
			else
			{
				winner.m_is_two_win = TRUE;
				phase = RELEASES;
			}

		}
		else if (spaceman.char_two.m_y > WINDOW_HEIGHT + (BLOCK_SIZE * 3))
		{
			if (sound_count == 0)soundsManager.Start(_T("GameEnd"), false);

			sound_count++;

			m_fc_finish++;
			m_fc_left_finish_move++;
			if (m_fc_finish <= 60 * 4)
			{
				draw.Draw(m_finish_left_y, 390, 0xffffffff, 0.0f, 0.0f, 600, 150, 1.0f, 0.5f, FINISH);
				draw.Draw(m_finish_right_y, 540, 0xffffffff, 0.0f, 0.5f, 600, 150, 1.0f, 0.5f, FINISH);
				if (m_fc_left_finish_move >= 2)
				{
					m_finish_left_y += m_left_scr;
					m_fc_left_finish_move = 0;

					if (m_finish_left_y >= 660)
					{
						m_left_scr = 0;
					}
				}

				if (m_fc_right_finish_move <= 2)
				{
					m_finish_right_y -= m_right_scr;
					m_fc_right_finish_move = 0;

					if (m_finish_right_y <= 660)
					{
						m_right_scr = 0;
					}
				}


				m_fc_background = 0;
			}
			else
			{
				winner.m_is_one_win = TRUE;
				phase = RELEASES;
			}
		}
		else
		{

			m_fc_ice_time_one++;
			m_fc_ice_time_two++;

			m_fc_background++;
			//縦スクロールのアニメーション
			if (m_fc_background >= 2)
			{
				m_game_bg_tu += SCROLL_SPEED;
				m_fc_background = 0;
				if (m_game_bg_tu <= -1.0f)
				{
					m_game_bg_tu = 0.0f;
				}
			}


			if (spaceman.char_one.m_is_create == TRUE)
			{
				m_fc_cereate_one--;

				if (m_fc_cereate_one == 0)
				{
					spaceman.char_one.m_is_create = FALSE;
					for (INT i = 0; i < CREATE_BLOCK_QUANITITY - 3; i++)
					{
						stage.create_block[i].m_x = -10000;
						stage.create_block[i].m_y = -10000;
					}
				}
			}

			if (spaceman.char_two.m_is_create == TRUE)
			{
				m_fc_cereate_two--;

				if (m_fc_cereate_two == 0)
				{
					spaceman.char_two.m_is_create = FALSE;
					for (INT i = 3; i < CREATE_BLOCK_QUANITITY; i++)
					{
						stage.create_block[i].m_x = -10000;
						stage.create_block[i].m_y = -10000;
					}
				}
			}



			//ブロックをスクロールに合わせて落とす処理
			for (INT i = 0; i < BLOCK_QUANTITY; i++)
			{
				stage.ScrollBlock(&stage.block[i]);
			}
			for (INT i = 0; i < CREATE_BLOCK_QUANITITY; i++)
			{
				stage.ScrollBlock(&stage.create_block[i]);
			}

			if (spaceman.char_one.m_is_jet == FALSE)
			{
				jet.UseJet(&spaceman.char_one);

			}
			if (spaceman.char_two.m_is_jet == FALSE)
			{
				jet.UseJet(&spaceman.char_two);

			}

			//重力
			spaceman.SpaceManMove(&spaceman.char_one, &spaceman.char_two, &spaceman.blast_one);
			spaceman.SpaceManMove(&spaceman.char_two, &spaceman.char_one, &spaceman.blast_two);

			//ブロックとの当たり判定
			for (INT i = 0; i < BLOCK_QUANTITY; i++)
			{
				collision.Hit_Block(stage.block[i], &spaceman.char_one);
				collision.Hit_Block(stage.block[i], &spaceman.char_two);
			}

			//クリエイトブロックとの当たり判定
			for (INT i = 0; i < CREATE_BLOCK_QUANITITY; i++)
			{
				collision.Hit_Block(stage.create_block[i], &spaceman.char_one);
				collision.Hit_Block(stage.create_block[i], &spaceman.char_two);
			}

			//アイスの
			if (spaceman.char_one.m_item_tu == 0.5f && spaceman.char_one.m_item_tv == 0.25f)
			{
				spaceman.char_one.m_is_ice = FALSE;
			}
			else
			{
				spaceman.char_one.m_is_ice = TRUE;
			}
			if (spaceman.char_two.m_item_tu == 0.5f && spaceman.char_two.m_item_tv == 0.25f)
			{
				spaceman.char_two.m_is_ice = FALSE;
			}
			else
			{
				spaceman.char_two.m_is_ice = TRUE;
			}
			//クリエイトの
			if (spaceman.char_one.m_item_tu == 0.25f && spaceman.char_one.m_item_tv == 0.0f)
			{
				spaceman.char_one.m_is_create = FALSE;
			}
			else
			{
				spaceman.char_one.m_is_create = TRUE;
			}
			if (spaceman.char_two.m_item_tu == 0.25f && spaceman.char_two.m_item_tv == 0.0f)
			{

				spaceman.char_two.m_is_create = FALSE;
			}
			else
			{
				spaceman.char_two.m_is_create = TRUE;
			}
			//ジェットの
			if (spaceman.char_one.m_item_tu == 0.75f && spaceman.char_one.m_item_tv == 0.0f)
			{
				spaceman.char_one.m_is_jet = FALSE;
			}
			else
			{
				spaceman.char_one.m_is_jet = TRUE;
			}
			if (spaceman.char_two.m_item_tu == 0.75f && spaceman.char_two.m_item_tv == 0.0f)
			{
				spaceman.char_two.m_is_jet = FALSE;
			}
			else
			{
				spaceman.char_two.m_is_jet = TRUE;
			}

			if (spaceman.char_one.m_is_ice_hit == FALSE) {
				if ((directx.KeyState[DIK_LSHIFT] == directx.PRESS||xinput[0]->IsKeyStrokePushed(CTRL::RSHOULDER)) 
					&& (spaceman.char_one.m_is_ice == FALSE))
				{
					ice.UseIce(&spaceman.char_one, &ice.ice_shot_one);
					m_fc_ice_time_one = 0;
					spaceman.char_one.m_item_tu = 0.0f;
					spaceman.char_one.m_item_tv = 0.0f;
				}
			}
			if (spaceman.char_two.m_is_ice_hit == FALSE) {
				if ((directx.KeyState[DIK_RSHIFT] == directx.PRESS|| xinput[1]->IsKeyStrokePushed(CTRL::RSHOULDER)) 
					&& (spaceman.char_two.m_is_ice == FALSE))
				{
					ice.UseIce(&spaceman.char_two, &ice.ice_shot_two);
					m_fc_ice_time_two = 0;
					spaceman.char_two.m_item_tu = 0.0f;
					spaceman.char_two.m_item_tv = 0.0f;
				}
			}
			if (ice.ice_shot_one.m_is_ice_move == TRUE)
			{
				if (ice.ice_shot_one.m_ice_direction == RIGHT) 
				{
					draw.Draw(ice.ice_shot_one.m_x, ice.ice_shot_one.m_y, 0xffffffff, 0.75f, 0.25f, ice.ice_shot_one.m_width, ice.ice_shot_one.m_height, 0.25f, 0.25f, ITEM);
					ice.MoveIce(&spaceman.char_one, &ice.ice_shot_one);
				}
				else if(ice.ice_shot_one.m_ice_direction == LEFT)
				{
					draw.Draw(ice.ice_shot_one.m_x, ice.ice_shot_one.m_y, 0xffffffff, 0.75f, 0.25f, ice.ice_shot_one.m_width, ice.ice_shot_one.m_height, 0.25f, 0.25f, ITEM, 180);
					ice.MoveIce(&spaceman.char_one, &ice.ice_shot_one);
				}
				else if (ice.ice_shot_one.m_ice_direction == UP)
				{
					draw.Draw(ice.ice_shot_one.m_x, ice.ice_shot_one.m_y, 0xffffffff, 0.75f, 0.25f, ice.ice_shot_one.m_width, ice.ice_shot_one.m_height, 0.25f, 0.25f, ITEM, 270);
					ice.MoveIce(&spaceman.char_one, &ice.ice_shot_one);
				}
				else if (ice.ice_shot_one.m_ice_direction == DOWN)
				{
					draw.Draw(ice.ice_shot_one.m_x, ice.ice_shot_one.m_y, 0xffffffff, 0.75f, 0.25f, ice.ice_shot_one.m_width, ice.ice_shot_one.m_height, 0.25f, 0.25f, ITEM, 90);
					ice.MoveIce(&spaceman.char_one, &ice.ice_shot_one);
				}
			}
			if (ice.ice_shot_two.m_is_ice_move == TRUE)
			{
				if (ice.ice_shot_one.m_ice_direction == RIGHT)
				{
					draw.Draw(ice.ice_shot_two.m_x, ice.ice_shot_two.m_y, 0xffffffff, 0.75f, 0.25f, ice.ice_shot_two.m_width, ice.ice_shot_two.m_height, 0.25f, 0.25f, ITEM);
					ice.MoveIce(&spaceman.char_two, &ice.ice_shot_two);
				}
				else if(ice.ice_shot_one.m_ice_direction == LEFT)
				{
					draw.Draw(ice.ice_shot_two.m_x, ice.ice_shot_two.m_y, 0xffffffff, 0.75f, 0.25f, ice.ice_shot_two.m_width, ice.ice_shot_two.m_height, 0.25f, 0.25f, ITEM, 180);
					ice.MoveIce(&spaceman.char_two, &ice.ice_shot_two);
				}
				else if (ice.ice_shot_one.m_ice_direction == UP)
				{
					draw.Draw(ice.ice_shot_two.m_x, ice.ice_shot_two.m_y, 0xffffffff, 0.75f, 0.25f, ice.ice_shot_two.m_width, ice.ice_shot_two.m_height, 0.25f, 0.25f, ITEM, 270);
					ice.MoveIce(&spaceman.char_two, &ice.ice_shot_two);
				}
				else if (ice.ice_shot_one.m_ice_direction == DOWN)
				{
					draw.Draw(ice.ice_shot_two.m_x, ice.ice_shot_two.m_y, 0xffffffff, 0.75f, 0.25f, ice.ice_shot_two.m_width, ice.ice_shot_two.m_height, 0.25f, 0.25f, ITEM, 90);
					ice.MoveIce(&spaceman.char_two, &ice.ice_shot_two);
				}
			}
			for (INT i = 0; i < BLOCK_QUANTITY; i++)
			{
				if (ice.IceHitBlockCheck(stage.block[i], ice.ice_shot_one) == TRUE)
				{
					ice.IceClear(&ice.ice_shot_one);
				}
				if (ice.IceHitBlockCheck(stage.block[i], ice.ice_shot_two) == TRUE)
				{
					ice.IceClear(&ice.ice_shot_two);
				}
			}

			if (ice.IceHitCharCheck(spaceman.char_two, ice.ice_shot_one) == TRUE)
			{
				//spaceman.char_one.is_ice = FALSE;
				ice.HitIceChar(&spaceman.char_two, &ice.ice_shot_one);
			}
			if (ice.IceHitCharCheck(spaceman.char_one, ice.ice_shot_two) == TRUE)
			{
				//spaceman.char_two.is_ice = FALSE;
				ice.HitIceChar(&spaceman.char_one, &ice.ice_shot_two);
			}

			//ウィンドウとの
			collision.HitWindow(&spaceman.char_one);
			collision.HitWindow(&spaceman.char_two);

			for (INT i = 0; i < BLOCK_X_MAX; i++)
			{
				stage.m_is_stage[i] = FALSE;
			}

			//ブロックを上に移動する処理
			for (INT i = 0; i < BLOCK_QUANTITY; i++)
			{
				if (stage.block[i].m_y >= BLOCK_SIZE * 2)
				{
					for (INT j = 0; j < BLOCK_QUANTITY; j++)
					{
						stage.MakeStage(&stage.block[j]);
					}

					break;
				}

			}

			if (stage.m_fc_item_pop <= 0)
			{
				for (INT i = 0; i < 10; i++)
				{
					if (spaceman.item_state[i].m_is_pop == FALSE)
					{
						stage.PopItem(&spaceman.item_state[i]);
						stage.m_fc_item_pop = 6 * 60;
						break;
					}

				}
			}
			else
			{
				stage.m_fc_item_pop--;
			}

			for (INT i = 0; i < 10; i++)
			{
				if (spaceman.item_state[i].m_is_pop == TRUE)
				{
					for (INT j = 0; j < BLOCK_QUANTITY; j++)
					{
						collision.HitBlockItem(stage.block[j], &spaceman.item_state[i]);
					}
					stage.ItemReset(&spaceman.item_state[i]);
					spaceman.item_state[i].m_y += spaceman.item_state[i].m_item_gravity;

					draw.Draw(spaceman.item_state[i].m_x, spaceman.item_state[i].m_y, 0xffffffff, 0.5f, 0.5f, spaceman.item_state[i].m_width, spaceman.item_state[i].m_height, 0.25f, 0.25f, ITEM);

					spaceman.item_state[i].m_item_gravity += 0.1f;
				}
			}

			//キャラとアイテムの当たり判定
			for (INT i = 0; i < 10; i++)
			{
				collision.Get_Item(&spaceman.char_one, &spaceman.item_state[i]);
				collision.Get_Item(&spaceman.char_two, &spaceman.item_state[i]);
			}
			//charとcharの当たり判定
			collision.Hit_Char(&spaceman.char_one, &spaceman.char_two);
			collision.Hit_Char(&spaceman.char_two, &spaceman.char_one);

			if (spaceman.char_one.m_is_ice_hit == FALSE) {
				//クリエイトを使った時の座標移動
				if ((directx.KeyState[DIK_LSHIFT] == directx.PRESS|| xinput[0]->IsKeyStrokePushed(CTRL::RSHOULDER)) 
					&& (spaceman.char_one.m_is_create == FALSE))
				{
					for (INT i = 0; i < CREATE_BLOCK_QUANITITY - 3; i++) {
						create.MakeBlock_Change(&spaceman.char_one, &stage.create_block[i], i);
						m_fc_cereate_one = 5 * 60;
						spaceman.char_one.m_item_tu = 0.0f;
						spaceman.char_one.m_item_tv = 0.0f;
					}
				}
			}
			if (spaceman.char_two.m_is_ice_hit == FALSE) {
				if ((directx.KeyState[DIK_RSHIFT] == directx.PRESS|| xinput[1]->IsKeyStrokePushed(CTRL::RSHOULDER)) 
					&& (spaceman.char_two.m_is_create == FALSE))
				{
					for (INT i = 3; i < CREATE_BLOCK_QUANITITY; i++) {
						create.MakeBlock_Change(&spaceman.char_two, &stage.create_block[i], i - 3);
						m_fc_cereate_two = 5 * 60;
						spaceman.char_two.m_item_tu = 0.0f;
						spaceman.char_two.m_item_tv = 0.0f;
					}
				}
			}
			//ブロックの描画
			for (INT i = 0; i < BLOCK_QUANTITY; i++)
			{
				stage.DrawBlock(stage.block[i]);
			}
			//クリエイトブロックの描画
			for (INT i = 0; i < CREATE_BLOCK_QUANITITY; i++)
			{
				stage.DrawBlock(stage.create_block[i]);
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			//中のアイコン
			draw.Draw(8.0f, 8.0f, 0xffffffff, spaceman.char_one.m_item_tu, spaceman.char_one.m_item_tv, 85.f, 85.f, 0.25f, 0.25f, ITEM);
			draw.Draw(WINDOW_WIDTH - 92.f, 8.0f, 0xffffffff, spaceman.char_two.m_item_tu, spaceman.char_two.m_item_tv, 85.f, 85.f, 0.25f, 0.25f, ITEM);
			//外枠
			draw.Draw(0.0f, 0.0f, 0xffffffff, 0.0f, 0.25f, 100.f, 100.f, 0.25f, 0.25f, ITEM);
			draw.Draw(WINDOW_WIDTH - 100.f, 0.0f, 0xffffffff, 0.0f, 0.25f, 100.f, 100.f, 0.25f, 0.25f, ITEM);


			//自機の描画1p
			draw.Draw(spaceman.char_one.m_x, spaceman.char_one.m_y, 0xffffffff, spaceman.char_one.m_tu, spaceman.char_one.m_tv, spaceman.char_one.m_width, spaceman.char_one.m_height, 0.25f, 0.03125f, CHARCTER);
			//自機の描画2p
			draw.Draw(spaceman.char_two.m_x, spaceman.char_two.m_y, 0xffffffff, spaceman.char_two.m_tu, spaceman.char_two.m_tv, spaceman.char_two.m_width, spaceman.char_two.m_height, 0.25f, 0.03125f, CHARCTER_TWO);

		}

	}
	else
	{
		m_fc_count++;
		if (m_count_tv < 1.0f)
		{
			draw.Draw(460, 40, 0xffffffff, 0.0f, m_count_tv, 1000, 1000, 1.0f, 0.25f, COUNTDOWN);
		}
		if (m_fc_count == 60)
		{
			m_count_tv += 0.25f;
		}
		if (m_fc_count == 120)
		{
			m_count_tv += 0.25f;
		}
		if (m_fc_count == 180)
		{
			m_count_tv += 0.25f;
		}
		if (m_fc_count == 240)
		{
			m_count_tv += 0.25f;
		}
		if (m_fc_count >= 241)
		{
			m_fc_count = 245;
			bgm = soundsManager.Start(_T("GameStart"), false);
		}
		//ブロックの描画
		for (INT i = 0; i < BLOCK_QUANTITY; i++)
		{
			stage.DrawBlock(stage.block[i]);
		}

		//自機の描画1p
		draw.Draw(spaceman.char_one.m_x, spaceman.char_one.m_y, 0xffffffff, spaceman.char_one.m_tu, spaceman.char_one.m_tv, spaceman.char_one.m_width, spaceman.char_one.m_height, 0.25f, 0.03125f, CHARCTER);
		//自機の描画2p
		draw.Draw(spaceman.char_two.m_x, spaceman.char_two.m_y, 0xffffffff, spaceman.char_two.m_tu, spaceman.char_two.m_tv, spaceman.char_two.m_width, spaceman.char_two.m_height, 0.25f, 0.03125f, CHARCTER_TWO);

	}

}

//ゲームのテクスチャの解放
VOID GAME::Release() {


	soundsManager.Stop(_T("GameBGM"));

	m_fc_count = 0.0f;
	m_count_tv = 0.0f;

	m_fc_finish = 0.0f;
	m_fc_left_finish_move = 0.0f;
	m_fc_right_finish_move = 0.0f;
	m_left_scr = 20;
	m_right_scr = 10;
	m_finish_left_y = -600;
	m_finish_right_y = 1920;

	//テクスチャの開放
	for (INT i = 0; i < TEX_MAX; i++)
	{
		if (directx.pTexture[i] != nullptr)
		{
			directx.pTexture[i]->Release();
			directx.pTexture[i] = nullptr;
		}
	}

	spaceman.ItemRelease(&spaceman.char_one,&spaceman.char_two);

	//リザルトシーンへ
	scene = RESULT_SCENE;
}
