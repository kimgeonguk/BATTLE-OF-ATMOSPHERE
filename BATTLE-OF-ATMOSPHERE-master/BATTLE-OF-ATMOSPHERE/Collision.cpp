#include "Collision.h"


VOID COLLISION::Hit_Block(BLOCK block, CHAR_* char_)
{
	if (char_->m_action == NO_JUMP)
	{
		char_->m_action = FALL;
	}
	if (char_->m_vec_y == 0 && char_->m_vec_x == 0 && char_->m_action == FALL)
	{
		char_->m_action = NO_JUMP;
	}

	Hit_Move(block, char_, char_->m_vec_x, 0);
	Hit_Move(block, char_, 0, char_->m_vec_y);
}

VOID COLLISION::HitWindow(CHAR_* char_)
{
	if (char_->m_y < -(BLOCK_SIZE * 2))
	{
		char_->m_gravity = 0;
		char_->m_y = -(BLOCK_SIZE * 2);
	}

	if (char_->m_x < -(BLOCK_SIZE * 2))
	{
		char_->m_x = -(BLOCK_SIZE * 2);
	}

	if (char_->m_x > WINDOW_WIDTH +(BLOCK_SIZE * 2))
	{
		char_->m_x = WINDOW_WIDTH +(BLOCK_SIZE * 2);
	}
}

VOID COLLISION::Hit_Move(BLOCK block, CHAR_* char_, FLOAT movement_x, FLOAT movement_y)
{

	if ((block.m_x < char_->m_x + char_->m_width) && (char_->m_x < block.m_x + block.m_width) && (block.m_y < char_->m_y + char_->m_height) && (char_->m_y < block.m_y + block.m_height))
	{
		if ((char_->m_save_y + char_->m_height <= block.m_y) || (char_->m_save_y >= block.m_y + block.m_height)) 
		{
			if (movement_y < 0)
			{
				char_->m_y = block.m_y - char_->m_height;
				char_->m_action = NO_JUMP;
				char_->m_gravity = SCROLL_SPEED_BLOCK;
				char_->m_is_call = FALSE;
			}
			else if (movement_y > 0)
			{
				char_->m_y = block.m_y + block.m_height;
				char_->m_gravity = 0;
			}
		}
		else
			//if(char_->save_x > block.x + block.m_width || char_->save_x + char_->m_width > block.x)
		{
			if (movement_x < 0)
			{
				char_->m_x = block.m_x - char_->m_width;
			}
			else if (movement_x > 0)
			{
				char_->m_x = block.m_x + block.m_width;
			}
		}
	}
}



VOID COLLISION::Hit_Char(CHAR_* char_one_, CHAR_* char_two_)
{
		if ((char_one_->m_x + char_one_->m_width > char_two_->m_x) && (char_one_->m_x < char_two_->m_x + char_two_->m_width) && (char_one_->m_y + char_one_->m_height > char_two_->m_y) && (char_one_->m_y < char_two_->m_y + char_two_->m_height)) {

			///////y軸
			if (char_one_->m_save_y + char_one_->m_height <= char_two_->m_save_y || char_two_->m_save_y + char_two_->m_height <= char_one_->m_save_y) {
				if (char_one_->m_save_y + char_one_->m_height <= char_two_->m_save_y)
				{
					char_one_->m_y = char_two_->m_y - char_one_->m_height;
					char_one_->m_gravity = 0;
					char_one_->m_action = NO_JUMP;
				}
				if (char_two_->m_save_y + char_two_->m_height <= char_one_->m_save_y)
				{
					char_two_->m_y = char_one_->m_y - char_two_->m_height;
					char_two_->m_gravity = 0;
					char_two_->m_action = NO_JUMP;
				}
			}
			else
			{
				///////x軸
				//１pが右から左へ
				if (char_one_->m_vec_x < 0 && char_two_->m_vec_x == 0)
				{
					char_two_->m_x = char_one_->m_x + char_one_->m_width;
				}
				//１pが左から右へ
				if (char_one_->m_vec_x > 0 && char_two_->m_vec_x == 0)
				{
					char_two_->m_x = char_one_->m_x - char_two_->m_width;
				}
				//２pが右から左へ
				if (char_two_->m_vec_x < 0 && char_one_->m_vec_x == 0)
				{
					char_one_->m_x = char_two_->m_x + char_two_->m_width;
				}
				//２pが左から右へ
				if (char_two_->m_vec_x > 0 && char_one_->m_vec_x == 0)
				{
					char_one_->m_x = char_two_->m_x - char_one_->m_width;
				}
				//１p左で両方動いているとき
				if (char_two_->m_vec_x * -1 == char_one_->m_vec_x && char_one_->m_vec_x <= 0)
				{
					FLOAT overlapped_half = char_one_->m_vec_x * -1 + char_two_->m_vec_x / 2;
					char_one_->m_x -= overlapped_half;
					char_two_->m_x += overlapped_half;
				}
				//２p左で両方動いているとき
				if (char_two_->m_vec_x * -1 == char_one_->m_vec_x && char_two_->m_vec_x <= 0)
				{
					FLOAT overlapped_half = char_one_->m_vec_x * -1 + char_two_->m_vec_x / 2;
					char_one_->m_x -= overlapped_half;
					char_two_->m_x += overlapped_half;
				}
			}
		}
}

VOID COLLISION::HitBlockItem(BLOCK block, ITEMSTATE* item_state)
{
	if ((block.m_x < item_state->m_x + item_state->m_width && block.m_y < item_state->m_y + item_state->m_height)
		&& (block.m_x + block.m_width > item_state->m_x && block.m_y + block.m_width > item_state->m_y))
	{
		item_state->m_item_gravity = 0;
		item_state->m_y = block.m_y - item_state->m_height;
	}
	else if ((block.m_x == item_state->m_x + item_state->m_width && block.m_y == item_state->m_y + item_state->m_height)
		&& (block.m_x + block.m_width == item_state->m_x && block.m_y + block.m_width == item_state->m_y))
	{
		item_state->m_item_gravity = 0;
		item_state->m_y += item_state->m_height;
	}
};


VOID COLLISION::Get_Item(CHAR_* char_,ITEMSTATE* item_state)
{
	if ((char_->m_x < item_state->m_x + item_state->m_width) && (char_->m_x + char_->m_width > item_state->m_x) && (char_->m_y < item_state->m_y + item_state->m_height) && (char_->m_y + char_->m_height > item_state->m_y))
	{
		switch (item_state->m_item_kind)
		{
		case ICE_ITEM:
			char_->m_item_tu = 0.5f;
			char_->m_item_tv = 0.25f;
				break;
		case CREATE_ITEM:
			char_->m_item_tu = 0.25f;
			char_->m_item_tv = 0.0f;
			break;
		case JET_ITEM:
			char_->m_item_tu = 0.75f;
			char_->m_item_tv = 0.0f;
			break;
		}

		item_state->m_x = -10000;
		item_state->m_y =-10100;
		item_state->m_item_gravity = 0.1f;
		item_state->m_is_pop = FALSE;
	}
}