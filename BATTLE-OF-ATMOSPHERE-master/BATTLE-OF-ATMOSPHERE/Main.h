#ifndef MAIN_H
#define MAIN_H

#include <windows.h>
#include <d3d9.h>

#include <SoundsManager.h>

#include "Draw.h"
#include "Xinput.h"

enum TEX
{
	TITLE_BG,
	TITLE_UI,
	TITLE_LOGO,
	CHARCTER,
	CHARCTER_TWO,
	COUNTDOWN,
	FINISH,
	BLAST,
	ITEM,
	GAME_STAGE,
	GAME_BG,
	HELP_BG,
	HELP_BG2,
	RESULT_BG,
	RESULT_LOGO,
	RESULT_UI,
	MAXTEX,
};

enum SCENE
{
	TITLE_SCENE,
	HELP_SCENE,
	GAME_SCENE,
	CLIMB_SCENE,
	EXIT_SCENE,
	RESULT_SCENE,
};


extern DIRECTX directx;

extern SCENE scene;

extern DRAW draw;

extern SoundLib::SoundsManager soundsManager;


//WinMain関数
INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdline, _In_ INT nCmdShow);

//ウィンドプロシージャの生成
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//window作成
HWND GenerateWindow(HWND* hWnd, HINSTANCE* hInstance, const TCHAR* API_NAME);

//メインループ
VOID Mainloop(MSG* msg);

#endif
