#include "Character.h"

#include "Main.h"

SPACEMAN::SPACEMAN()
{
	xinput[0] = Xinput::GetInstance(Player::ONE);
	xinput[1] = Xinput::GetInstance(Player::TWO);
}

VOID SPACEMAN::SpaceManInit(CHAR_* char_)
{//x,tu,tv,方向
	if (char_->player == ONE_PLAYER)
	{
		char_->m_x = 96 * 5;
		char_->m_tu = 0.0f;
		char_->m_tv = 0.0f;
		char_->m_direction = RIGHT;
		char_->m_side_direction = RIGHT;
	}
	if (char_->player == TWO_PLAYER)
	{
		char_->m_x = 96 * 14;
		char_->m_tu = 0.0f;
		char_->m_tv = 0.0f;
		char_->m_direction = LEFT;
		char_->m_side_direction = LEFT;
	}
	//y,wiwdth,height,ジャンプの状態
	char_->m_y = 96 * 6;
	char_->m_width = 75;
	char_->m_height = 150;
	char_->m_action = FALL;
	
	char_->m_gravity = 1.0f;


	///アイテム
	//使えるかどうか
	char_->m_is_create = FALSE;
	char_->m_is_jet = FALSE;
	char_->m_is_ice = FALSE;
	char_->m_charge = TRUE;
	char_->m_is_ice_hit = FALSE;
	//フレームカウント
	char_->m_fc_ice = 0;
	char_->m_fc_charge = 0;
	char_->m_fc_jet = 0;
	char_->m_fc_push = 0;
	

}

VOID SPACEMAN::SpaceManJumpSwitchChange(JUMP* jump)
{
	switch (*jump)
	{
	case FALL:
		*jump = ONE_JUMP;
		break;
	case ONE_JUMP:
		*jump = TWO_JUMP;
		break;
	}
}

VOID SPACEMAN::SpaceManSwitchJump(CHAR_* char_)
{
	switch (char_->m_action)
	{
	case FALL:

		char_->m_gravity += 1;
		
		if (char_->m_direction == UP)
		{
			if (char_->m_side_direction == RIGHT)
			{
				char_->m_tu = 0.0f;
				char_->m_tv = 0.03125f * 1;
			}
			else if (char_->m_side_direction == LEFT)
			{
				char_->m_tu = 0.0f;
				char_->m_tv = 0.0f;
			}
		}
		else if (char_->m_direction == DOWN)
		{
			if (char_->m_side_direction == RIGHT)
			{
				char_->m_tu = 0.0f;
				char_->m_tv = 0.03125f * 1;
			}
			else if (char_->m_side_direction == LEFT)
			{
				char_->m_tu = 0.0f;
				char_->m_tv = 0.0f;
			}
		}



		if (char_->m_direction == RIGHT) {
			char_->m_tu = 0.0f;
			char_->m_tv = 0.03125f * 1;
		}
		else if (char_->m_direction == LEFT)
		{
			char_->m_tu = 0.0f;
			char_->m_tv = 0.0f;
		}
		break;

	case NO_JUMP:

		char_->m_is_call = FALSE;
		char_->m_gravity += 1;
		if (char_->m_direction == RIGHT) {
			char_->m_tu = 0.0f;
			char_->m_tv = 0.03125f * 1;
		}
		else if (char_->m_direction == LEFT)
		{
			char_->m_tu = 0.0f;
			char_->m_tv = 0.0f;
		}

		break;

	case ONE_JUMP:

		char_->m_gravity += 1;

		if (char_->m_side_direction == RIGHT) {
			char_->m_tu = 0.25f;
			char_->m_tv = 0.03125f * 20;
		}
		else if (char_->m_side_direction == LEFT)
		{
			char_->m_tu = 0.25f;
			char_->m_tv = 0.03125f * 21;
		}

		break;

	case TWO_JUMP:

		if (char_->m_is_call == FALSE)
		{
			char_->m_is_call = TRUE;
		}

		char_->m_gravity += 1;

		if (char_->m_side_direction == RIGHT) {
			char_->m_tu = 0.25f;
			char_->m_tv = 0.03125f * 20;
		}
		else if (char_->m_side_direction == LEFT)
		{
			char_->m_tu = 0.25f;
			char_->m_tv = 0.03125f * 21;
		}


		break;

	default:

		char_->m_gravity += 1;

		break;
	}
}

BOOL SPACEMAN::BlastHitCheck(CHAR_ char_, BLAST_STATUS blast_status)
{
	if ((blast_status.m_x < char_.m_x + char_.m_width) && (blast_status.m_y < char_.m_y + char_.m_height) && (blast_status.m_x + blast_status.m_size > char_.m_x) && (blast_status.m_y + blast_status.m_size > char_.m_y))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

VOID SPACEMAN::SpaceManPush(CHAR_* char_me, CHAR_* char_you, BLAST_STATUS* blast_status)
{
	switch (char_me->m_direction)
	{
	case RIGHT:
		blast_status->m_x = char_me->m_x + 96.0f;
		blast_status->m_y = char_me->m_y + 48.0f;
		blast_status->m_tu = 128.0f * 1 / 2048.f;
		blast_status->m_tv = 128.0f * 0 / 2048.f;
		break;
	case LEFT:
		blast_status->m_x = char_me->m_x - 96.0f;
		blast_status->m_y = char_me->m_y + 48.0f;
		blast_status->m_tu = 128.0f * 1 / 2048.f;
		blast_status->m_tv = 128.0f * 1 / 2048.f;
		break;
	case UP:
		blast_status->m_x = char_me->m_x;
		blast_status->m_y = char_me->m_y - 96.0f;
		blast_status->m_tu = 128.0f * 1 / 2048.f;
		blast_status->m_tv = 128.0f * 2 / 2048.f;
		char_me->m_gravity = 5;
		break;
	case DOWN:
		blast_status->m_x = char_me->m_x;
		blast_status->m_y = char_me->m_y + 192.0f;
		blast_status->m_tu = 128.0f * 1 / 2048.f;
		blast_status->m_tv = 128.0f * 3 / 2048.f;
		break;
	}

	draw.Draw(blast_status->m_x, blast_status->m_y, 0xffffffff, blast_status->m_tu, blast_status->m_tv, blast_status->m_size, blast_status->m_size,128.0f/ 2048, 128.0f/2048, BLAST);

	if (BlastHitCheck(*char_you, *blast_status) == TRUE)
	{
		if (char_you->m_is_guard == FALSE)
		{
			char_you->m_is_hit = TRUE;

			switch (char_me->m_direction)
			{
			case RIGHT:
				blast_status->m_blast_power_x = 80;
				blast_status->m_blast_power_y = 0;
				break;
			case LEFT:
				blast_status->m_blast_power_x = -80;
				blast_status->m_blast_power_y = 0;
				break;
			case UP:
				blast_status->m_blast_power_x = 0;
				blast_status->m_blast_power_y = -80;
				break;
			case DOWN:
				blast_status->m_blast_power_x = 0;
				blast_status->m_blast_power_y = 80;
				break;
			}
		}
	}

	char_me->m_fc_push = 30;

}

VOID SPACEMAN::SpaceManBlastHit(CHAR_* char_, BLAST_STATUS* blast_status)
{
	if (blast_status->m_blast_power_x != 0 || blast_status->m_blast_power_y != 0)
	{
		if (blast_status->m_blast_power_x != 0)
		{
			char_->m_x += blast_status->m_blast_power_x;

			if (blast_status->m_blast_power_x > 0)
			{
				blast_status->m_blast_power_x -= 20;
				char_->m_tu = 0.5f;
				char_->m_tv = 0.03125f * 6;
			}
			else
			{
				blast_status->m_blast_power_x += 20;
				char_->m_tu = 0.5f;

				char_->m_tv = 0.03125f * 6;
			}

		}

		if (blast_status->m_blast_power_y != 0)
		{
			char_->m_y += blast_status->m_blast_power_y;

			if (blast_status->m_blast_power_y > 0)
			{
				blast_status->m_blast_power_y -= 20;
			}
			else
			{
				blast_status->m_blast_power_y += 20;
			}
		}

	}
	else 
	{
		char_->m_is_hit = FALSE;
	}

}

VOID SPACEMAN::SpaceManDash(CHAR_* char_)
{
	if (char_->m_is_dash == TRUE) {

		if (char_->player == ONE_PLAYER)
		{
			if ((directx.KeyState[DIK_D] == directx.ON && directx.KeyState[DIK_G] == directx.ON) ||
				(directx.KeyState[DIK_A] == directx.ON && directx.KeyState[DIK_G] == directx.ON))
			{
				char_->m_plus_spaceman_speed += m_plus_dash_power;
				char_->m_plus_jump_power += m_plus_dash_power;

				if (char_->m_plus_spaceman_speed >= m_max_plus_spaceman_power)
				{
					char_->m_plus_spaceman_speed = m_max_plus_spaceman_power;
					char_->m_plus_jump_power = m_max_plus_spaceman_power;
				}
			}
			else if (directx.KeyState[DIK_G] == directx.OFF)
			{
				char_->m_plus_spaceman_speed = 0.0F;
				char_->m_plus_jump_power = 0.0F;
			}

		}

		if (char_->player == TWO_PLAYER)
		{
			if ((directx.KeyState[DIK_RIGHT] == directx.ON && directx.KeyState[DIK_L] == directx.ON) || 
				(directx.KeyState[DIK_LEFT] == directx.ON && directx.KeyState[DIK_L] == directx.ON))
			{
				char_->m_plus_spaceman_speed += m_plus_dash_power;
				char_->m_plus_jump_power += m_plus_dash_power;

				if (char_->m_plus_spaceman_speed >= m_max_plus_spaceman_power)
				{
					char_->m_plus_spaceman_speed = m_max_plus_spaceman_power;
					char_->m_plus_jump_power = m_max_plus_spaceman_power;
				}
			}
			else if (directx.KeyState[DIK_L] == directx.OFF)
			{
				char_->m_plus_spaceman_speed = 0.0F;
				char_->m_plus_jump_power = 0.0F;
			}
		}
	}
}

VOID SPACEMAN::SpaceManMove(CHAR_* char_, CHAR_* char_you, BLAST_STATUS* blast_status)
{	

	char_->m_save_x = char_->m_x;
	char_->m_save_y = char_->m_y;
	//1p用
	if (char_->player == ONE_PLAYER) {

		if (char_->m_direction == RIGHT || char_->m_direction == LEFT)
		{
			char_->m_side_direction = char_->m_direction;
		}

		SpaceManSwitchJump(char_);

		if (char_you->m_is_hit == TRUE)
		{
			SpaceManBlastHit(char_you, blast_status);
		}
		else if (char_->m_is_ice_hit == TRUE)
		{
			if (char_->m_direction == UP)
			{
				if (char_->m_side_direction == RIGHT) {
					char_->m_tu = 0.0f;
					char_->m_tv = 0.03125f * 22;
				}
				else if (char_->m_side_direction == LEFT) {
					char_->m_tu = 0.0f;
					char_->m_tv = 0.03125f * 23;
				}
			}else
			if (char_->m_direction == DOWN)
			{
				if (char_->m_side_direction == RIGHT) {
					char_->m_tu = 0.0f;
					char_->m_tv = 0.03125f * 22;
				}
				else if (char_->m_side_direction == LEFT) {
					char_->m_tu = 0.0f;
					char_->m_tv = 0.03125f * 23;
				}
			}

			if (char_->m_direction == RIGHT) {
				char_->m_tu = 0.0f;
				char_->m_tv = 0.03125f * 22;
			}
			else if(char_->m_direction == LEFT){
				char_->m_tu = 0.0f;
				char_->m_tv = 0.03125f * 23;
			}
			
			char_->m_fc_ice--;
			if (char_->m_fc_ice <= 0)
			{
				char_->m_is_ice_hit = FALSE;
			}
		}
		else
		{
			if (directx.KeyState[DIK_S] == directx.OFF && xinput[0]->IsKeyStrokePressed(CTRL::TRIGGER_LEFT) == FALSE) {

				if (directx.KeyState[DIK_D] == directx.ON || xinput[0]->IsKeyStrokePressed(CTRL::LTHUMB_RIGHT))
				{
					char_->m_x += (char_->m_spaceman_speed + char_->m_plus_spaceman_speed);

					char_->m_direction = RIGHT;
					if (char_->m_action == ONE_JUMP || char_->m_action == TWO_JUMP)
					{
						char_->m_tu = 0.25f;
						char_->m_tv = 0.03125f * 20;
					}
					else
					{
						char_->m_tu = 0.0f;
						char_->m_tv = 0.03125f * 1;
					}
				}
				else if (directx.KeyState[DIK_A] == directx.ON || xinput[0]->IsKeyStrokePressed(CTRL::LTHUMB_LEFT))
				{
					char_->m_x -= (char_->m_spaceman_speed + char_->m_plus_spaceman_speed);
					char_->m_direction = LEFT;
					if (char_->m_action == ONE_JUMP || char_->m_action == TWO_JUMP)
					{
						char_->m_tu = 0.25f;
						char_->m_tv = 0.03125f * 21;
					}
					else
					{
						char_->m_tu = 0.0f;
						char_->m_tv = 0.03125f * 0;
					}
				}

				SpaceManDash(char_);

				char_->m_fc_push--;

				if (directx.KeyState[DIK_LCONTROL] == directx.PRESS || xinput[0]->IsKeyStrokePushed(CTRL::TRIGGER_RIGHT))
				{
					if (char_->m_fc_push <= 0)
					{
						SpaceManPush(char_, char_you, blast_status);
						if (char_->m_direction == RIGHT && (char_->m_action == ONE_JUMP || char_->m_action == TWO_JUMP))
						{
							char_->m_tu = 0.5f;
							char_->m_tv = 0.03125f * 19;
						}
						else if (char_->m_direction == LEFT && (char_->m_action == ONE_JUMP || char_->m_action == TWO_JUMP))
						{
							char_->m_tu = 0.5f;
							char_->m_tv = 0.03125f * 4;
						}
						else if (char_->m_direction == RIGHT)
						{
							char_->m_tu = 0.5f;
							char_->m_tv = 0.03125f * 1;
						}
						else if (char_->m_direction == LEFT)
						{
							char_->m_tu = 0.5f;
							char_->m_tv = 0.03125f * 0;
						}
					}
				}
			}
			if ((directx.KeyState[DIK_W] == directx.PRESS || xinput[0]->IsKeyStrokePushed(CTRL::BUTTON_A)) && (char_->m_is_call == FALSE))
			{
				char_->m_gravity = -30;
				SpaceManJumpSwitchChange(&char_->m_action);
				char_->m_direction = UP;
			}

			if (directx.KeyState[DIK_S] == directx.ON || xinput[0]->IsKeyStrokePressed(CTRL::TRIGGER_LEFT))
			{
				if (char_->m_action == NO_JUMP || char_->m_action == FALL)
				{
					char_->m_is_dash = FALSE;
					char_->m_is_guard = TRUE;
					if (char_->m_side_direction == RIGHT) {
						char_->m_tu = 0.5f;
						char_->m_tv = 0.03125f * 15;
					}
					else if (char_->m_side_direction == LEFT)
					{
						char_->m_tu = 0.5f;
						char_->m_tv = 0.03125f * 16;
					}
				}
				char_->m_direction = DOWN;
			}
			else if (directx.KeyState[DIK_S] == directx.RELEASE || xinput[0]->IsKeyStrokeReleased(CTRL::TRIGGER_LEFT))
			{
				if (char_->m_action == NO_JUMP || char_->m_action == FALL)
				{
					char_->m_is_guard = FALSE;
					char_->m_is_dash = TRUE;
					if (char_->m_side_direction == RIGHT)
					{
						char_->m_tu = 0.0f;
						char_->m_tv = 0.03125f * 1;
					}
					else if (char_->m_side_direction == LEFT)
					{
						char_->m_tu = 0.0f;
						char_->m_tv = 0.03125f * 0;
					}
				}
			}
		}
	}
	//２p用
	if (char_->player == TWO_PLAYER) {
		//今どっちの方向を向いているか→side
		if (char_->m_direction == RIGHT || char_->m_direction == LEFT)
		{
			char_->m_side_direction = char_->m_direction;
		}
		//ジャンプの状態を変える
		SpaceManSwitchJump(char_);

		//押し出しが当たったか
		if (char_you->m_is_hit == TRUE)
		{
			//押し出しが当たった
			SpaceManBlastHit(char_you, blast_status);
		}
		//アイスが当たっているか
		else if (char_->m_is_ice_hit == TRUE)
		{
			//方向が上
			if (char_->m_direction == UP)
			{//方向が上で右の時
				if (char_->m_side_direction == RIGHT)
				{
					char_->m_tu = 0.0f;
					char_->m_tv = 0.03125f * 22;
				}
				//方向が上で左の時
				else if (char_->m_side_direction == LEFT)
				{
					char_->m_tu = 0.0f;
					char_->m_tv = 0.03125f * 23;
				}
			}
			//方向が下
			if (char_->m_direction == DOWN)
			{
				//方向が下で右の時
				if (char_->m_side_direction == RIGHT)
				{
					char_->m_tu = 0.0f;
					char_->m_tv = 0.03125f * 22;
				}
				//方向が下で左の時
				else if (char_->m_side_direction == LEFT)
				{
					char_->m_tu = 0.0f;
					char_->m_tv = 0.03125f * 23;
				}
			}
			//方向が右の時
			if (char_->m_direction == RIGHT)
			{
				char_->m_tu = 0.0f;
				char_->m_tv = 0.03125f * 22;
			}
			//方向が左の時
			else if (char_->m_direction == LEFT)
			{
				char_->m_tu = 0.0f;
				char_->m_tv = 0.03125f * 23;
			}
			//アイスの凍っている時間のフレームカウント
			char_->m_fc_ice--;
			//フレームカウントが０以下になったら解除
			if (char_->m_fc_ice <= 0)
			{
				char_->m_is_ice_hit = FALSE;
			}
		}
		else
		{
			//下キー
			if (directx.KeyState[DIK_DOWN] == directx.OFF && xinput[1]->IsKeyStrokePressed(CTRL::TRIGGER_LEFT) == FALSE)
			{
				//右キー
				if (directx.KeyState[DIK_RIGHT] == directx.ON || xinput[1]->IsKeyStrokePressed(CTRL::LTHUMB_RIGHT))
				{
					char_->m_x += (char_->m_spaceman_speed + char_->m_plus_spaceman_speed);
					char_->m_direction = RIGHT;
					if (char_->m_action == ONE_JUMP || char_->m_action == TWO_JUMP)
					{
						char_->m_tu = 0.25f;
						char_->m_tv = 0.03125f * 20;
					}
					else
					{
						char_->m_tu = 0.0f;
						char_->m_tv = 0.03125f * 1;
					}
				}
				//左キー
				else if (directx.KeyState[DIK_LEFT] == directx.ON || xinput[1]->IsKeyStrokePressed(CTRL::LTHUMB_LEFT))
				{
					char_->m_x -= (char_->m_spaceman_speed + char_->m_plus_spaceman_speed);
					char_->m_direction = LEFT;
					if (char_->m_action == ONE_JUMP || char_->m_action == TWO_JUMP)
					{
						char_->m_tu = 0.25f;
						char_->m_tv = 0.03125f * 21;
					}
					else
					{
						char_->m_tu = 0.0f;
						char_->m_tv = 0.03125f * 0;
					}

				}

				SpaceManDash(char_);

				char_->m_fc_push--;
				//押し出し
				if (directx.KeyState[DIK_RCONTROL] == directx.PRESS || xinput[1]->IsKeyStrokePushed(CTRL::TRIGGER_RIGHT))
				{
					if (char_->m_fc_push <= 0)
					{
						SpaceManPush(char_, char_you, blast_status);
						if (char_->m_direction == RIGHT && (char_->m_action == ONE_JUMP || char_->m_action == TWO_JUMP))
						{
							char_->m_tu = 0.5f;
							char_->m_tv = 0.03125f * 19;
						}
						else if (char_->m_direction == LEFT && (char_->m_action == ONE_JUMP || char_->m_action == TWO_JUMP))
						{
							char_->m_tu = 0.5f;
							char_->m_tv = 0.03125f * 4;
						}
						else if (char_->m_direction == RIGHT)
						{
							char_->m_tu = 0.5f;
							char_->m_tv = 0.03125f * 1;
						}
						else if (char_->m_direction == LEFT)
						{
							char_->m_tu = 0.5f;
							char_->m_tv = 0.03125f * 0;
						}
					}
				}
			}
			//上キー
			if ((directx.KeyState[DIK_UP] == directx.PRESS||xinput[1]->IsKeyStrokePushed(CTRL::BUTTON_A)) && (char_->m_is_call == FALSE))
			{
				char_->m_gravity = -30;
				SpaceManJumpSwitchChange(&char_->m_action);

				char_->m_direction = UP;
			}

			if (directx.KeyState[DIK_DOWN] == directx.ON|| xinput[1]->IsKeyStrokePressed(CTRL::TRIGGER_LEFT))
			{
				char_->m_direction = DOWN;
				
				if (char_->m_action == NO_JUMP || char_->m_action == FALL)
				{
					char_->m_is_guard = TRUE;
					char_->m_is_dash = FALSE;
					if (char_->m_side_direction == RIGHT)
					{
						char_->m_tu = 0.5f;
						char_->m_tv = 0.03125f * 15;
					}
					else
					if (char_->m_side_direction == LEFT)
					{
						char_->m_tu = 0.5f;
						char_->m_tv = 0.03125f * 16;
					}
				}
			//下キー離したとき
			}
			else if (directx.KeyState[DIK_DOWN] == directx.RELEASE || xinput[1]->IsKeyStrokeReleased(CTRL::TRIGGER_LEFT))
			{
				if (char_->m_action == NO_JUMP || char_->m_action == FALL)
				{
					char_->m_is_guard = FALSE;
					char_->m_is_dash = TRUE;
					if (char_->m_side_direction == RIGHT)
					{
						char_->m_tu = 0.0f;
						char_->m_tv = 0.03125f * 1;
					}
					else if (char_->m_side_direction == LEFT)
					{
						char_->m_tu = 0.0f;
						char_->m_tv = 0.03125f * 0;
					}
				}
			}
		}
	}
	Move(char_, char_->m_save_x, char_->m_save_y);
}
	


VOID SPACEMAN::Move(CHAR_* char_, FLOAT m_save_x, FLOAT m_save_y)
{

	//重力移動
	char_->m_y += char_->m_gravity;

	//当たり判定用の処理（毎フレームごとに更新）
	char_->m_vec_x = m_save_x - char_->m_x;
	char_->m_vec_y = m_save_y - char_->m_y;
}

VOID SPACEMAN::ItemRelease(CHAR_* char_one, CHAR_* char_two)
{
	char_one->m_is_create = FALSE;
	char_one->m_is_ice = FALSE;
	char_one->m_is_jet = FALSE;

	char_two->m_is_create = FALSE;
	char_two->m_is_ice = FALSE;
	char_two->m_is_jet = FALSE;

	char_one->m_item_tu = 0.0f;
	char_one->m_item_tv = 0.0f;

	char_two->m_item_tu = 0.0f;
	char_two->m_item_tv = 0.0f;
}
