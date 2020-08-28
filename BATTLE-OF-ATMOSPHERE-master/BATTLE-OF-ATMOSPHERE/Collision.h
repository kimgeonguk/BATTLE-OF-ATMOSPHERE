#ifndef COLLISION_H_
#define COLLISION_H_

#include <Windows.h>

#include "Stage.h"
#include "Character.h"
#include"DirectX.h"

class COLLISION
{
public:
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
	 VOID Hit_Block(BLOCK block, CHAR_* char_);
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
	VOID HitWindow(CHAR_* char_);
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
	VOID Hit_Move(BLOCK block, CHAR_* char_, FLOAT movement_x, FLOAT movement_y);

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
	VOID Hit_Char(CHAR_* char_one, CHAR_* char_two);
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
	VOID HitBlockItem(BLOCK block, ITEMSTATE* item_state);
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
	VOID Get_Item(CHAR_* char_, ITEMSTATE* item_state);


};

#endif