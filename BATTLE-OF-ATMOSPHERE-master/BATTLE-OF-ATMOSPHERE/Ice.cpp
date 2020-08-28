#include "Ice.h"
#include"Main.h"

VOID ICE::Init_Ice(ICE_SHOT* ice_shot)
{
	ice_shot->m_x = 100000;
	ice_shot->m_y = 100000;
	ice_shot->m_width = 96.0f;
	ice_shot->m_height = 96.0f;
}
VOID ICE::UseIce(CHAR_* char_, ICE_SHOT* ice_shot)
{
	ice_shot->m_is_ice_move = TRUE;
	ShotIce_Change(char_, ice_shot);
	ice_shot->m_ice_direction = char_->m_direction;
	char_->m_is_ice = TRUE;
}
VOID ICE::ShotIce_Change(CHAR_* char_, ICE_SHOT* ice_shot)
{
	switch (ice_shot->m_ice_direction)
	{
	case RIGHT:
		Right_ShotIce(char_, ice_shot);
		break;
	case LEFT:
		Left_ShotIce(char_, ice_shot);
		break;
	case UP:
		Up_ShotIce(char_, ice_shot);
		break;
	case DOWN:
		Down_ShotIce(char_, ice_shot);
		break;
	}
}
VOID ICE::MoveIce(CHAR_* char_, ICE_SHOT* ice_shot)
{
	EvaporatingIce(char_, ice_shot);
	switch (ice_shot->m_ice_direction)
	{
	case RIGHT:
		ice_shot->m_x += m_ice_speed;
		ice_shot->m_y += SCROLL_SPEED_BLOCK;
		break;
	case LEFT:
		ice_shot->m_x -= m_ice_speed;
		ice_shot->m_y += SCROLL_SPEED_BLOCK;
		break;
	case UP:
		ice_shot->m_y -= m_ice_speed;
		ice_shot->m_y += SCROLL_SPEED_BLOCK;
		break;
	case DOWN:
		ice_shot->m_y += m_ice_speed;
		ice_shot->m_y += SCROLL_SPEED_BLOCK;
		break;
	}
}
BOOL ICE::IceHitCharCheck(CHAR_ char_, ICE_SHOT ice_shot)
{
	if ((ice_shot.m_x < char_.m_x + char_.m_width && ice_shot.m_y < char_.m_y + char_.m_height) && (ice_shot.m_x + ice_shot.m_width > char_.m_x && ice_shot.m_y + ice_shot.m_height > char_.m_y))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
BOOL ICE::IceHitBlockCheck(BLOCK block, ICE_SHOT ice_shot)
{
	if ((ice_shot.m_x < block.m_x + block.m_width && ice_shot.m_y < block.m_y + block.m_height) && (ice_shot.m_x + ice_shot.m_width > block.m_x && ice_shot.m_y + ice_shot.m_height > block.m_y))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

VOID ICE::EvaporatingIce(CHAR_* char_, ICE_SHOT* ice_shot)
{
	if (ice_shot->m_x < 0 || ice_shot->m_x>1920 || ice_shot->m_y < 0 || ice_shot->m_y>1080)
	{
		char_->m_is_ice = FALSE;
		IceClear(ice_shot);
	}
}

VOID ICE::HitIceChar(CHAR_* char_, ICE_SHOT* ice_shot)
{
	char_->m_is_ice_hit = TRUE;
	char_->m_fc_ice = 3 * 60;
	IceClear(ice_shot);
}
VOID ICE::Right_ShotIce(CHAR_* char_, ICE_SHOT* ice_shot)
{
	ice_shot->m_x = char_->m_x + char_->m_width;
	ice_shot->m_y = char_->m_y + char_->m_height / 2 - ice_shot->m_height / 2;
}
VOID ICE::Left_ShotIce(CHAR_* char_, ICE_SHOT* ice_shot)
{
	ice_shot->m_x = char_->m_x - ice_shot->m_width;
	ice_shot->m_y = char_->m_y + char_->m_height / 2 - ice_shot->m_height / 2;
}
VOID ICE::Up_ShotIce(CHAR_* char_, ICE_SHOT* ice_shot)
{
	ice_shot->m_x = char_->m_x;
	ice_shot->m_y = char_->m_y - char_->m_height / 2;
}
VOID ICE::Down_ShotIce(CHAR_* char_, ICE_SHOT* ice_shot)
{
	ice_shot->m_x = char_->m_x;
	ice_shot->m_y = char_->m_y + char_->m_height;
}

VOID ICE::IceClear(ICE_SHOT* ice_shot)
{
	ice_shot->m_is_ice_move = FALSE;
	ice_shot->m_x = -10000000;
	ice_shot->m_y = -10000000;
}
