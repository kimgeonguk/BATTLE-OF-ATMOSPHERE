#ifndef DRAW_H_
#define DRAW_H_

#include <windows.h>
#include <d3d9.h>

#include "DirectX.h"

//カスタムバーテックス
struct CUSTOMVERTEX
{
	FLOAT x, y, z, rhw;
	DWORD color;
	FLOAT tu, tv;
};


class DRAW
{
public:
	VOID Rotate(CUSTOMVERTEX  original[], CUSTOMVERTEX rotatevertex[], DOUBLE degree = 0.0f);

	//描画関数
	VOID Draw(FLOAT x, FLOAT y, DWORD color, FLOAT tu, FLOAT tv, FLOAT width, FLOAT height, FLOAT tu_width, FLOAT tv_height, INT texture, DOUBLE degree = 0.0f);

	//アニメーション関数
	VOID Animetion(INT*, INT, FLOAT*, FLOAT*, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT, FLOAT);

	//テクスチャを読み込む
	VOID LoadTexture(const CHAR* file_name, INT TEX);

	DOUBLE to_Rad(DOUBLE degree);
};



#endif