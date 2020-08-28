#include "Main.h"
#include "DirectX.h"

#include "TitleScene.h"
#include "HelpScene.h"
#include "GameScene.h"
#include"ClimbScene.h"
#include "ResultScene.h"
#include "Stage.h"
#include "Collision.h"
#include "Create.h"
#include "Jet.h"
#include "Ice.h"

//ここ出来ればなくしたい
DIRECTX directx;
DRAW draw;
TITLE title;
HELP help;
GAME game;
CLIMB climb;
RESULT result;
STAGE stage;
SPACEMAN spaceman;
COLLISION collision;
CREATE create;
JET jet;
ICE ice;

SCENE scene = TITLE_SCENE;

BOOL isSuccess = false;

SoundLib::SoundsManager soundsManager;

//メイン
INT WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PSTR lpCmdline, _In_ INT nCmdShow)
{
	HWND hWnd = NULL;
	const TCHAR api_name[] = _T("BATTLE-OF-ATMOSHERE");
	//メッセージ
	MSG msg;
	hWnd = GenerateWindow(&hWnd, &hInstance, api_name);
	directx.BuildDxDevice(hWnd, _T("Blank.jpg"));

	
	soundsManager.Initialize();

	Mainloop(&msg);


	//ウィンドウ情報をみて更新
	ShowWindow(hWnd, SW_SHOW);

	UpdateWindow(hWnd);

	directx.All_Release();

	return (INT)msg.wParam;
}

//ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	//メッセージ別の処理
	switch (msg)
	{
		//ウィンドウが破壊されたときのメッセージ
	case WM_DESTROY:
		//閉じるメッセージを送る
		PostQuitMessage(0);
		return 0;
		//ユーザーがメニューかALTキーと何かを押したとき
	case WM_SYSKEYDOWN:
		switch (wp)
		{
		case VK_RETURN:
			return 0;
		case VK_F4:
			//閉じるメッセ―ジ
			PostMessage(hWnd, WM_CLOSE, 0, 0);
			return 0;
		default:
			return 0;
		}
		return 0;
	}
	//DefaultWindowProcedureを返す(デフォルト)
	return DefWindowProc(hWnd, msg, wp, lp);
}


//
HWND GenerateWindow(HWND* hWnd, HINSTANCE* hInstance, const TCHAR* p_api_name)
{
	//ウィンドウクラス
	WNDCLASS Wndclass;
	Wndclass.style = CS_HREDRAW | CS_VREDRAW; //ウィンドウスタイル
	Wndclass.lpfnWndProc = WndProc; //ウィンドウプロシージャ
	Wndclass.cbClsExtra = 0; //メモリ確保
	Wndclass.cbWndExtra = 0; //メモリ確保
	Wndclass.hInstance = *hInstance;	//ハンドルインスタンス
	Wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	Wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);	//カーソル
	Wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //背景のブラシ,色
	Wndclass.lpszMenuName = NULL; //メニュー画面の名前
	Wndclass.lpszClassName = p_api_name; //アプリケーションの名前

	//ウィンドウクラスの登録
	RegisterClass(&Wndclass);

	//ウィンドウハンドルにcreatewindow関数で作った情報を代入
	return *hWnd = CreateWindow(
		p_api_name,							//クラスの名前
		p_api_name,							//アプリケーションのタイトル
		(WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,	//ウィンドウのスタイル
//		WS_VISIBLE | WS_POPUP,	//ウィンドウのスタイル
0,		            				//Xの位置
0,		            				//Yの位置
WINDOW_WIDTH,								//幅
WINDOW_HEIGHT,								//高さ
NULL,								//親ウィンドウのハンドル
NULL,								//メニューのハンドル
*hInstance,							//インスタンスハンドル
NULL								//メッセージに渡されるパラメータ
);
}

//メインループ
VOID Mainloop(MSG* msg)
{

	DWORD Prev = timeGetTime();
	DWORD Curr;

	timeBeginPeriod(1);


	ZeroMemory(msg, sizeof(msg));
	while (msg->message != WM_QUIT)
	{
		if (PeekMessage(msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(msg);
			DispatchMessage(msg);
		}
		else
		{
			Curr = timeGetTime();
			if (Curr - Prev >= 1000 / 60)
			{

				directx.pD3Device->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0x00, 0x00, 0x00), 1.0, 0);

				directx.pD3Device->BeginScene();

				directx.UpdateKeyState();

				Xinput::GetInstance(Player::ONE)->UpdateController();
				Xinput::GetInstance(Player::TWO)->UpdateController();

				//ここからゲーム処理
				switch (scene)
				{
				case TITLE_SCENE:
					title.Title_Scene();
					break;
				case HELP_SCENE:
					help.Help_Scene();
					break;
				case GAME_SCENE:
					game.Game_Scene();
					break;
				case CLIMB_SCENE:
					climb.Climb_Scene();
					break;
				case RESULT_SCENE:
					result.Result_Scene();
					break;
				default:
					MessageBox(0, _T("シーン設定がされていません"), NULL, MB_OK);
				}
				directx.pD3Device->EndScene();
				directx.pD3Device->Present(NULL, NULL, NULL, NULL);

				Prev = Curr;

				if (directx.KeyState[DIK_ESCAPE] == directx.PRESS)
				{
					Xinput::Destroy();
					PostQuitMessage(0);
				}
			}
		}
		Sleep(1);
	}
	timeEndPeriod(1);
}
