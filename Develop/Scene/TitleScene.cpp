#include "TitleScene.h"
#include "../Utility/InputManager.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"

TitleScene::TitleScene()
{
	back_ground_image = NULL;
}

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	ResourceManager* rm = ResourceManager::GetInstance();
	// 背景画像の読み込み
	back_ground_image = rm->GetImages("Resource/images/title.png")[0];

	//UIの読み込み
	mario_ui = rm->GetImages("Resource/images/UI/name_mario.png")[0];
	mario_time = rm->GetImages("Resource/images/UI/time.png")[0];
	mario_world = rm->GetImages("Resource/images/UI/world.png")[0];
	mario_coin = rm->GetImages("Resource/images/UI/uicoin.png")[0];

}

eSceneType TitleScene::Update(const float& delta_second)
{

	// 入力情報を取得
	InputManager* input = InputManager::GetInstance();

	// インゲームシーンに遷移する
  	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::in_game;
	}
	/*if (input->GetButtonDown(XINPUT_BUTTON_START))
	{
		return eSceneType::in_game;
	}*/

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

void TitleScene::Draw() const
{

	DrawExtendGraph(0, 0, 640, 480, back_ground_image,FALSE);   //背景の描画

	//タイトルUIの描画
	DrawGraph(340, 10, mario_world,TRUE);
	DrawGraph(480, 10, mario_time,TRUE);
	DrawGraph(100, 10, mario_ui, TRUE);
	DrawGraph(150, 25, mario_coin, TRUE);

	//// 親クラスの描画処理を呼び出す
	//__super::Draw();

	//// UIの描画
	//SetFontSize(60);
	//DrawFormatString(120, 140, GetColor(255, 255, 0), "P A C - M A N");
	//SetFontSize(40);
	//DrawFormatString(10, 640, GetColor(255, 0, 0), "Space key pressed game start");
	//SetFontSize(16);
}

void TitleScene::Finalize()
{

	 //親クラスの終了時処理を呼び出す
	__super::Finalize();
}

const eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::title;
}
