#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <Windows.h>

#include "Xinput.h"

enum JUMP
{
	FALL,       //! 
	NO_JUMP,	//! ジャンプしていない
	ONE_JUMP,	//! 1回ジャンプした
	TWO_JUMP	//! 二段ジャンプした
};


enum DIRECTION
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
};

enum PLAYER
{
	ONE_PLAYER,
	TWO_PLAYER,
};

enum ITEM_
{
	ICE_ITEM,
	CREATE_ITEM,
	JET_ITEM,
	MAX_ITEM,
	/*GRAVITY_ITEM,
	IMPACT_ITEM,*/
};

typedef struct
{
	FLOAT m_x, m_y,m_tu,m_tv;
	FLOAT m_blast_power_x, m_blast_power_y = 0.0f;
	FLOAT m_size;
}BLAST_STATUS;

typedef struct
{
	///プレイヤー
	PLAYER player;                                   //! playerの１pか２ｐ保存している関数
	FLOAT m_x, m_y, m_tu, m_tv, m_width, m_height;   //! キャラクターのx, y, tu, tv, width, height
	FLOAT m_vec_x, m_vec_y;                          //! 今移動している方向を割り出す
	JUMP m_action = FALL;                            //! 今のジャンプ状態
	DIRECTION m_direction;                           //! 向いている方向→全方向
	DIRECTION m_side_direction;                      //! 向いている方向->横方向
	DIRECTION m_item_direction;                      //!アイテムを使った時の向いている方向
	FLOAT m_gravity = 0.0f;                          //! 自機にかかる重力
	FLOAT m_save_x;                                  //! 移動前のｘ
	FLOAT m_save_y;                                  //! 移動前のｙ
	// 歩行関係変数
	FLOAT m_spaceman_speed = 8.0F;                   //! 自機の移動速度
	//押し出し関係
	BOOL m_is_hit = FALSE;                           //! 押し出しに当たったかどうか判断する関数
	FLOAT m_fc_push = 0.0f;                          //! 押し出しのクールタイムをカウントするフレームカウント
	//ガード関係
	BOOL m_is_guard = FALSE;						 //! 現在ガード中かどうかを判断する用フラグ
	//ダッシュ関係
	BOOL m_is_dash = FALSE;                          //! 現在ジャンプが可能かどうかを判断する用フラグ
	FLOAT m_plus_spaceman_speed = 0.0F;              //! ダッシュ時の現在の速度加速量
	FLOAT m_plus_jump_power = 0.0F;                  //! ダッシュ時、上昇したジャンプ量
	
	BOOL m_is_call = FALSE;                          //! 呼ばれたかどうか判断する用フラグ
	///アイテム
	//持っているアイテムのtuとtv
	FLOAT m_item_tu, m_item_tv;

	//使えるか判断するためのフラグ
	BOOL m_is_create = FALSE;                          //!クリエイトを使えるか判断するフラグ
	BOOL m_is_ice = FALSE;                             //!アイスを使えるか判断するフラグ
	BOOL m_is_jet = FALSE;                             //!ジェットを使えるか判断するフラグ
	//ジェット関係
	BOOL m_jet_right = FALSE;
	BOOL m_jet_left = FALSE;
	BOOL m_jet_up = FALSE;
	INT m_fc_jet = 0;
	INT m_fc_charge = 0;
	FLOAT m_jet_speed = 20.0f;
	BOOL m_charge = FALSE;
	//アイス関係
	BOOL m_is_ice_hit = FALSE;
	FLOAT m_fc_ice = 0.0f;

	INT blast_count = 0;
	BOOL blast = FALSE;
}CHAR_;


typedef struct
{
	BOOL m_is_pop = FALSE;
	FLOAT m_x, m_y;
	FLOAT m_width = 96.0f;
	FLOAT m_height = 96.0f;
	FLOAT m_item_gravity = 0.1f;
	ITEM_ m_item_kind;
}ITEMSTATE;

/**
* @brief 自機のステータスのベース
*/
class SPACEMAN
{
private:

	CONST FLOAT m_max_plus_spaceman_power = 5.0F;    //! ダッシュ時の最大加速量
	CONST FLOAT m_plus_dash_power = 0.05F;           //! ダッシュの加速度

	Xinput* xinput[2];

public:

	// 歩行関係変数
	CONST FLOAT m_max_gravity = 0.2F;				

	BLAST_STATUS blast_one = { 0,0,0.0f,0.0f,0,0,96.0f };
	BLAST_STATUS blast_two = { 0,0,0.0f,0.0f,0,0,96.0f };

	CHAR_ char_one = {ONE_PLAYER};
	CHAR_ char_two = {TWO_PLAYER};

	ITEMSTATE item_state[10];

	/**
	* @fn VOID SpaceManRelease()
	*/
	VOID SpaceManInit(CHAR_* char_);

	SPACEMAN();

	BOOL BlastHitCheck(CHAR_ char_, BLAST_STATUS blast_status);

	/**
	* @fn VOID SpaceManPush(CHAR_* char_me, CHAR_* char_you, BLAST_STATUS* blast_status)
	* @brief 
	*/
	VOID SpaceManPush(CHAR_* char_me, CHAR_* char_you, BLAST_STATUS* blast_status);

	/**
	* @fn VOID SpaceManBlastHit(CHAR_* char_, BLAST_STATUS* blast_status)
	* @brief 押し出された（吹っ飛ばされる）ときの処理
	*/
	VOID SpaceManBlastHit(CHAR_* char_, BLAST_STATUS* blast_status);

	/**
	* @fn VOID SpaceManDash(CHAR_ char_, PLAYER player)
	*/
	VOID SpaceManDash(CHAR_* char_);
	/**
	* @fn VOID SpaceManMove(CHAR_* char_, PLAYER player)
	* @param PLAYER player 1Pか2Pかを判断している
	*/
	VOID SpaceManMove(CHAR_* char_, CHAR_* char_you, BLAST_STATUS* blast_status);

	/**
	* @fn VOID SpaceManJumpSwitchChange(INT* jump)
	* @param (INT jump) 現在のジャンプ状態
	* @brief ジャンプボタンが押されたときジャンプ状態を切り替える
	*/
	VOID SpaceManJumpSwitchChange(JUMP* jump);

	/**
	* @fn VOID SpaceManSwitchJump(INT jump)
	* @param (CHAR_* char_) 現在のジャンプ状態
	* @brief 現在のジャンプ状態に応じて処理を行う関数
	*/
	VOID SpaceManSwitchJump(CHAR_* char_);

	VOID Move(CHAR_* char_, FLOAT save_x, FLOAT save_y);

	VOID ItemRelease(CHAR_* char_one, CHAR_* char_two);
};

#endif // !CHARACTER_H_

