#ifndef ICE_H_
#define ICE_H_
#include <Windows.h>
#include "Character.h"
#include"GameScene.h"
#include"Stage.h"
typedef struct
{
	DIRECTION m_ice_direction;
	BOOL m_is_ice_move = FALSE;
	FLOAT m_x, m_y;//適当な値で初期化
	FLOAT m_width, m_height;
}ICE_SHOT;

class ICE
{
public:

	CONST FLOAT m_ice_speed = 10.0f;
/**
 * @fn
 * キャラクターとアイスが当たったか当たっていないかを判断する関数
 * @brief アイスの矩形とキャラが当たっているかを判断する
 * @param (char_) キャラクターの情報を渡す
 * @param (ice_shot) アイスの情報を渡す
 * @return BOOL
 * @detail アイスの矩形とのキャラの矩形が当たっていたら、trueを返しほかの時にfalseを返す
 */
	BOOL IceHitCharCheck(CHAR_ char_, ICE_SHOT ice_shot);
	/**
 * @fn
 * ブロックとアイスが当たったか当たっていないかを判断する関数
 * @brief アイスの矩形とブロックが当たっているかを判断する
 * @param (block) ブロックの情報を渡す
 * @param (ice_shot) アイスの情報を渡す
 * @return BOOL
 * @detail アイスの矩形とのブロックの矩形が当たっていたら、trueを返しほかの時にfalseを返す
 */
	BOOL IceHitBlockCheck(BLOCK block, ICE_SHOT ice_shot);
	/**
 * @fn
 * アイスを初期化
 * @brief アイスの情報を初期化
 * @param (ice_shot) アイスの情報を渡す
 * @detail アイスのm_x,m_y,width,heightを初期化する
 */
	VOID Init_Ice(ICE_SHOT* ice_shot);
	/**
 * @fn
 * 
 * @brief アイスを使う時の関数
 * @param (char_) キャラクターの情報を渡す
 * @param (ice_shot) アイスの情報を渡す
 * @detail 
 */
	VOID UseIce(CHAR_* char_, ICE_SHOT* ice_shot);
/**
 * @fn
 * アイスの使う方向を割り出す
 * @brief アイスの使う方向をm_directionから割り出し
 * @param (chra_) キャラクターの情報を渡す
 * @param (ice_shot) アイスの情報を渡す
 * @detail 
 */
	VOID ShotIce_Change(CHAR_* char_, ICE_SHOT* ice_shot);
/**
* @fn
* アイスが画面の外にでたときにアイスを消去する
* @brief 要約説明
* @param (chra_) キャラクターの情報を渡す
* @param (ice_shot) アイスの情報を渡す
* @detail 
*/
	VOID EvaporatingIce(CHAR_* char_, ICE_SHOT* ice_shot);
/**
 * @fn
 * ここに関数の説明を書く
 * @brief 要約説明
 * @param (引数名) 引数の説明
 * @param (引数名) 引数の説明
 * @return 戻り値の説明
 * @sa 参照すべき関数を書けばリンクが貼れる
 * @detail 詳細な説明
 */
	VOID Right_ShotIce(CHAR_* char_, ICE_SHOT* ice_shot);
/**
 * @fn
 * ここに関数の説明を書く
 * @brief 要約説明
 * @param (引数名) 引数の説明
 * @param (引数名) 引数の説明
 * @return 戻り値の説明
 * @sa 参照すべき関数を書けばリンクが貼れる
 * @detail 詳細な説明
 */
	VOID Left_ShotIce(CHAR_* char_, ICE_SHOT* ice_shot);
/**
 * @fn
 * ここに関数の説明を書く
 * @brief 要約説明
 * @param (引数名) 引数の説明
 * @param (引数名) 引数の説明
 * @return 戻り値の説明
 * @sa 参照すべき関数を書けばリンクが貼れる
 * @detail 詳細な説明
 */
	VOID Up_ShotIce(CHAR_* char_, ICE_SHOT* ice_shot);
/**
 * @fn
 * ここに関数の説明を書く
 * @brief 要約説明
 * @param (引数名) 引数の説明
 * @param (引数名) 引数の説明
 * @return 戻り値の説明
 * @sa 参照すべき関数を書けばリンクが貼れる
 * @detail 詳細な説明
 */
	VOID Down_ShotIce(CHAR_* char_, ICE_SHOT* ice_shot);
/**
* @fn
* ここに関数の説明を書く
* @brief 要約説明
* @param (引数名) 引数の説明
* @param (引数名) 引数の説明
* @return 戻り値の説明
* @sa 参照すべき関数を書けばリンクが貼れる
* @detail 詳細な説明
*/
	VOID MoveIce(CHAR_* char_, ICE_SHOT* ice_shot);
	
 /**
* @fn
* ここに関数の説明を書く
* @brief 要約説明
* @param (引数名) 引数の説明
* @param (引数名) 引数の説明
* @return 戻り値の説明
* @sa 参照すべき関数を書けばリンクが貼れる
* @detail 詳細な説明
*/
	VOID HitIceChar(CHAR_* char_, ICE_SHOT* ice_shot);
/**
* @fn
* ここに関数の説明を書く
* @brief 要約説明
* @param (引数名) 引数の説明
* @param (引数名) 引数の説明
* @return 戻り値の説明
* @sa 参照すべき関数を書けばリンクが貼れる
* @detail 詳細な説明
*/
	ICE_SHOT ice_shot_one = { RIGHT,FALSE,100000,100000,96.0f,96.0f };
/**
* @fn
* ここに関数の説明を書く
* @brief 要約説明
* @param (引数名) 引数の説明
* @param (引数名) 引数の説明
* @return 戻り値の説明
* @sa 参照すべき関数を書けばリンクが貼れる
* @detail 詳細な説明
*/
	ICE_SHOT ice_shot_two = { LEFT,FALSE,-100000,-100000,96.0f,96.0f };

	VOID IceClear(ICE_SHOT* ice_shot);
};

#endif