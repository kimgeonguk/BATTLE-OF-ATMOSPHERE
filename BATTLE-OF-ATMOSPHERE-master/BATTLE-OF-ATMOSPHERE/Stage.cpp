#include "Stage.h"
#include "Collision.h"
#include "MapChip.h"




VOID STAGE::SlotChange(CHAR_ char_)
{

}

VOID STAGE::PopItem(ITEMSTATE* item_state)
{
	INT item_x_pos = rand() % (BLOCK_X_MAX - 1);
	INT item_y_pos = rand() % (BLOCK_Y_MAX - 5);

	item_state->m_is_pop = TRUE;
	item_state->m_x = item_x_pos * BLOCK_SIZE;
	item_state->m_y = item_y_pos * BLOCK_SIZE;
	item_state->m_item_kind = (ITEM_)(rand() % 3);
}

VOID STAGE::ItemReset(ITEMSTATE* item_state)
{
	if (item_state->m_y > WINDOW_HEIGHT + (BLOCK_SIZE * 2))
	{
		item_state->m_item_gravity = 0.1f;
		item_state->m_is_pop = FALSE;
	}
}

VOID STAGE::InitStageBlock()
{
	for (INT i = 0; i < 8; i++)
	{
		block[i].m_x = (6 + i) * BLOCK_SIZE;
		block[i].m_y = -4 * BLOCK_SIZE;
	}

	for (INT i = 0; i < 10; i++)
	{
		block[i + 8].m_x = (5 + i) * BLOCK_SIZE;
		block[i + 8].m_y = 2 * BLOCK_SIZE;
	}
	for (INT i = 0; i < 14; i++)
	{
		block[i + 19].m_x = (3 + i) * BLOCK_SIZE;
		block[i + 19].m_y = 8 * BLOCK_SIZE;
	}

	for (INT i = 0; i < 5; i++)
	{
		block[i + 33].m_x = i * BLOCK_SIZE;
		block[i + 33].m_y = -10 * BLOCK_SIZE;
	}

	for (INT i = 0; i < 5; i++)
	{
		block[i + 38].m_x = (15 + i) * BLOCK_SIZE;
		block[i + 38].m_y = -10 * BLOCK_SIZE;
	}
}

VOID STAGE::InitClimbStageBlock()
{

}


VOID STAGE::InitBlock()
{
	//ブロックの初期値
	for (INT i = 0; i < BLOCK_QUANTITY; i++)
	{
		block[i].m_x = -10000.f;//初期値適当
		block[i].m_y = -10000.f;//初期値適当
		block[i].m_tu = 0.0f;
		block[i].m_tv = 0.0f;
		block[i].m_width = BLOCK_SIZE;
		block[i].m_height = BLOCK_SIZE;
	}
	//クリエイトブロックの初期値
	for (INT i = 0; i < CREATE_BLOCK_QUANITITY; i++)
	{
		create_block[i].m_x = -10000.f;//初期値適当
		create_block[i].m_y = -10000.f;//初期値適当
		create_block[i].m_tu = 96.f / 192.f;
		create_block[i].m_tv = 0.0f;
		create_block[i].m_width = BLOCK_SIZE;
		create_block[i].m_height = BLOCK_SIZE;
	}

	InitStageBlock();
}

VOID STAGE::MakeStage(BLOCK* block)
{
	if (block->m_y >= WINDOW_HEIGHT + (BLOCK_SIZE * 8))
	{
		do
		{
			block->m_x_num = rand() % (BLOCK_X_MAX - 1);
		} 
		while (m_is_stage[block->m_x_num] == TRUE);

		m_is_stage[block->m_x_num] = TRUE;
		block->m_x = (block->m_x_num) * BLOCK_SIZE;
		block->m_y = -(BLOCK_SIZE * 4);
	}
}

VOID STAGE::ClimbMakeStage(BLOCK* block)
{
	if (block->m_y >= WINDOW_HEIGHT + (BLOCK_SIZE * 8))
	{
		do
		{
			block->m_x_num = rand() % (BLOCK_X_MAX - 1);
		} while (m_is_stage[block->m_x_num] == TRUE);

		m_is_stage[block->m_x_num] = TRUE;

		switch (rand()% 3 + 1)
		{
		case 1:
			block->m_x = (block->m_x_num) * BLOCK_SIZE;
			block->m_y = -(BLOCK_SIZE * 5);
			break;
		case 2:
			block->m_x = (block->m_x_num) * BLOCK_SIZE;
			block->m_y = -(BLOCK_SIZE * 4);
			break;
		case 3:
			block->m_x = (block->m_x_num) * BLOCK_SIZE;
			block->m_y = -(BLOCK_SIZE * 3);
			break;
		default:
			block->m_x = (block->m_x_num) * BLOCK_SIZE;
			block->m_y = -(BLOCK_SIZE * 4);
			break;
		}
	}
}

VOID STAGE::ScrollBlock(BLOCK* block)
{
	block->m_y += SCROLL_SPEED_BLOCK;
}

VOID STAGE::ClimbScrollBlock(BLOCK* block,INT plus_scroll_speed)
{
	block->m_y += SCROLL_SPEED_BLOCK + plus_scroll_speed;
}

VOID STAGE::FallBlock()
{




}

VOID STAGE::DrawBlock(BLOCK block)
{
	draw.Draw(block.m_x, block.m_y, 0xffffffff, block.m_tu, block.m_tv, block.m_width, block.m_height, 96.f / 192.f, 96.f / 192.f, GAME_STAGE, 0);
}

VOID STAGE::StopBlock(BLOCK* block)
{
	block->m_y -= SCROLL_SPEED_BLOCK;
}