#ifndef CREATE_H_
#define CREATE_H_


#include <Windows.h>

#include "Character.h"
#include "Stage.h"


class CREATE
{
public:
/**
 * @fn
 * ブロックを出す方向判断する関数
 * @brief 向いている方向からクリエイトする方向を決める関数
 * @param (char_) キャラの情報を渡す 
 * @param (block) ブロックの情報を渡す
 * @param (ite) アイテムの番号を渡す
 * @detail キャラのm_directionで方向を割り出し呼び出す関数を変える、is_createをtrueにし使えなくする
 */
	VOID MakeBlock_Change(CHAR_* char_, BLOCK* block, INT ite);
/**
 * @fn
 * 右にブロックを生成する
 * @brief ブロックを３つ右側に生成する
 * @param (char_) キャラの情報を渡す 
 * @param (block) ブロックの情報を渡す
 * @param (i) アイテムの番号を渡す
 * @sa VOID MakeBlock_Change(CHAR_* char_, BLOCK* block, INT ite);
 * @detail 右側に３つの画面外に描画してあったブロックの位置を移動させる
 */
	VOID Right_MakeBlock(CHAR_* char_, BLOCK* block, INT i);
	/**
 * @fn
 * 左にブロックを生成する
 * @brief ブロックを３つ左側に生成する
 * @param (char_) キャラの情報を渡す 
 * @param (block) ブロックの情報を渡す
 * @param (i) アイテムの番号を渡す
 * @sa VOID MakeBlock_Change(CHAR_* char_, BLOCK* block, INT ite);
 * @detail 左側に３つの画面外に描画してあったブロックの位置を移動させる
 */
	VOID Left_MakeBlock(CHAR_* char_, BLOCK* block, INT i);
	/**
 * @fn
 * 上にブロックを生成する
 * @brief ブロックを３つ上側に生成する
 * @param (char_) キャラの情報を渡す 
 * @param (block) ブロックの情報を渡す
 * @param (i) アイテムの番号を渡す
 * @sa VOID MakeBlock_Change(CHAR_* char_, BLOCK* block, INT ite);
 * @detail 上側に３つの画面外に描画してあったブロックの位置を移動させる
 */
	VOID Up_MakeBlock(CHAR_* char_, BLOCK* block, INT i);
	/**
 * @fn
 * 下にブロックを生成する
 * @brief ブロックを３つ下側に生成する
 * @param (char_) キャラの情報を渡す 
 * @param (block) ブロックの情報を渡す
 * @param (i) アイテムの番号を渡す
 * @sa VOID MakeBlock_Change(CHAR_* char_, BLOCK* block, INT ite);
 * @detail 下側に３つの画面外に描画してあったブロックの位置を移動させる
 */
	VOID Down_MakeBlock(CHAR_* char_, BLOCK* block, INT i);


};



#endif
