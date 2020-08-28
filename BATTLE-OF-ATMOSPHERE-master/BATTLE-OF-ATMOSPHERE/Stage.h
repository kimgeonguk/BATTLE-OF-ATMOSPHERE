#ifndef STAGE_H_
#define STAGE_H_

#include <Windows.h>
#include "Character.h"


//ブロックの大きさ
#define BLOCK_SIZE 96.f
//ブロックの個数
#define BLOCK_QUANTITY 45
//ブロックのWindowのwidth
#define BLOCK_X_MAX 20
//ブロックのWindowのheight
#define BLOCK_Y_MAX 11
//クリエイトブロックの個数
#define CREATE_BLOCK_QUANITITY 6
//スクロールのスピード
#define SCROLL_SPEED  -0.001f
//ブロックのスクロールするスピード
#define SCROLL_SPEED_BLOCK 1.0f

typedef struct {
	INT m_x_num;
	FLOAT m_x, m_y, m_width, m_height, m_tu, m_tv;
}BLOCK;

class STAGE {
public:

	FLOAT m_fc_item_pop = 5 * 60;

	BOOL m_is_stage[20] = {};
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
	VOID SlotChange(CHAR_ char_);
/**
 * @fn
 * アイテムをポップする
 * @brief アイテムをランダムでポップさせる
 * @param (item_state) アイテムの情報
 * @detail 
 */
	VOID PopItem(ITEMSTATE* item_state);
/**
 * @fn
 * アイテムを元に戻す
 * @brief アイテムをブロックの消えるところに来た時リセットされる
 * @param (item_state) アイテムの情報
 * @detail アイテムをブロックと同じ座標に来た時にリセットされる
 */
	VOID ItemReset(ITEMSTATE* item_state);
/**
 * @fn
 * ステージの初期化
 * @brief ステージの初期化
 * @detail ステージ用のブロックを初期化
 */
	VOID InitStageBlock();
/**
 * @fn
 * ブロックを初期化
 * @brief ブロックの初期化
 * @detail ブロックとクリエイトブロックの初期化
 */
	VOID InitBlock();

/**
 * @fn
 * ステージの初期化
 * @brief ステージの初期化
 * @detail クライムステージ用のブロックを初期化
 */
	VOID InitClimbStageBlock();
/**
 * @fn
 * ブロックをウィンドウより下でブロックを上に戻す
 * @brief ブロックをウィンドウから３マス下でブロックの座標を上にする
 * @param (block) ブロックの情報
 * @detail ブロックのｙ座標がウィンドウから３マス下でブロックの座標を上にする
 */
	VOID MakeStage(BLOCK* block);

	VOID ClimbMakeStage(BLOCK* block);
/**
 * @fn
 * ブロックを下げる関数
 * @brief ブロックを下げる
 * @param (block) ブロックの情報
 * @detail ブロックを下げる
 */
	VOID ScrollBlock(BLOCK* block);

/**
 * @fn
 * ここに関数の説明を書く
 * @brief 要約説明
 * @detail 詳細な説明
 */
	VOID FallBlock();

/**
 * @fn
 * ブロックを描画する
 * @brief ブロックを描画する
 * @param (block) ブロックの情報
 * @detail ブロックを情報
 */
	VOID DrawBlock(BLOCK block);

	VOID ClimbScrollBlock(BLOCK* block,INT plus_speed);


	BLOCK block[BLOCK_QUANTITY];

	BLOCK create_block[CREATE_BLOCK_QUANITITY];

	VOID StopBlock(BLOCK* block);
};

#endif
