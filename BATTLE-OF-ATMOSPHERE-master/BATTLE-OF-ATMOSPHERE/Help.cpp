#include "../BATTLE-OF-ATMOSPHERE/HelpScene.h"
#include"../BATTLE-OF-ATMOSPHERE/MapChip.h"

//タイトルのフェーズの宣言
HELP::SCENE_PHASE Phase = HELP::LOAD;
//
//MapchipLoading Mp;
//DrawMap map;

//タイトルのフェーズの移動
void HELP::Help_Scene() {

	switch (Phase) {
	case LOAD:
		Loading();
		break;
	case PROCESSING:
		Process();
		break;
	case RELEASES:
		Release();
		Phase = LOAD;
		break;
	}
}

//タイトルのテクスチャの読み込み
void HELP::Loading() {

	Phase = PROCESSING;

}

//タイトルの描画処理
void HELP::Process() {

	//エンターでゲームへ
	if (directx.KeyState[DIK_RETURN] == directx.PRESS) {
		Phase = RELEASES;

	}
}

//タイトルのテクスチャの解放
void HELP::Release() {

	for (int i = 0; i < TEX_MAX; i++) {
		if (directx.pTexture[i] != nullptr) {
			directx.pTexture[i]->Release();
			directx.pTexture[i] = nullptr;
		}
	}

	scene = GAMESCENE;

}
