#include "TitleScene.h"
#include "../Utility/InputManager.h"
#include "../Utility/ResourceManager.h"
#include "DxLib.h"

TitleScene::TitleScene() :
	mario_coin_ui(),
	kakeru_ui(),
	coin_num_min(),
	coin_num_sec()
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
	mario_coin_ui = rm->GetImages("Resource/images/Item/coin.png",4,4,1,32,32);
	kakeru_ui = rm->GetImages("Resource/images/Ui/num.png", 14, 14, 1, 16, 16);

	//同じ一枚の画像を入れる
	//コイン取得数
	coin_num_min = kakeru_ui;
	coin_num_sec = kakeru_ui;
}

eSceneType TitleScene::Update(const float& delta_second)
{

	// 入力情報を取得
	InputManager* input = InputManager::GetInstance();

	// インゲームシーンに遷移する
	// シーン遷移用のキーを一時的に変更(変更前：スペースキー 変更後:エンターキー)
  	if (input->GetKeyDown(KEY_INPUT_RETURN))
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
	DrawGraph(50, 10, mario_ui, TRUE);
	//コインの画像
	DrawGraph(160, 25, mario_coin_ui[0], TRUE);  //コインの画像
	DrawGraph(190, 33, kakeru_ui[11], TRUE);     //コイン横の×
	DrawGraph(210, 34, coin_num_min[0], TRUE);   //コイン10の位の数字
	DrawGraph(230, 34, coin_num_sec[0], TRUE);   //コイン１の位の数字
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
