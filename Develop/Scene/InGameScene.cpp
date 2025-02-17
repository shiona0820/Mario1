#include "InGameScene.h"

#include "../Utility/ResourceManager.h"
#include "../Utility/InputManager.h"
#include "../Utility/StageData.h"


#include "../Objects/Mario/Player.h"
#include "../Objects/Enemy/kuribo.h"
#include "../Objects/Enemy/nokonoko.h"

#include "../Objects/Item/coin.h"

#include "DxLib.h"
#include <fstream>



InGameScene::InGameScene() :
	kakeru_ui(),
	coin_num_min(),
	coin_num_sec()
{
	back_ground_BGM = NULL;
}

InGameScene::~InGameScene()
{
	screen_offset.y = D_OBJECT_SIZE * 3.0f;
}

void InGameScene::Initialize()
{

	ResourceManager* rm = ResourceManager::GetInstance();
	//メインBGMの読み込み
	back_ground_BGM = rm->GetSounds("Resource/Sounds/BGM_MarioGround.wav");

	StageData* Stage = StageData::GetInstance();
	Stage->Load();

	//マリオの表示
	player = CreateObject<Player>(Vector2D(100, 403));
	//クリボーの表示
	Kuribo = CreateObject<kuribo>(Vector2D(750, 403));
	Nokonoko = CreateObject<nokonoko>(Vector2D(350, 385));

	//アニメーションしているコインの表示
	Coin = CreateObject<coin>(Vector2D(175, 45));


	//UIの読み込み
	mario_ui = rm->GetImages("Resource/images/UI/name_mario.png")[0];
	mario_time = rm->GetImages("Resource/images/UI/time.png")[0];
	mario_world = rm->GetImages("Resource/images/UI/world.png")[0];

	kakeru_ui = rm->GetImages("Resource/images/Ui/num.png", 14, 14, 1, 16, 16);

	//同じ一枚の画像を入れる
	//コイン取得数
	coin_num_min = kakeru_ui;
	coin_num_sec = kakeru_ui;
}

eSceneType InGameScene::Update(const float& delta_second)
{
	StageData* Stage = StageData::GetInstance();
	Stage->Update(delta_second);

	//BGMが流れていないときに再生
	if (CheckSoundMem(back_ground_BGM) != TRUE)
	{
		//メインBGMの再生
		PlaySoundMem(back_ground_BGM, DX_PLAYTYPE_LOOP, TRUE);
	}

	//画面右端かつ動いてるときに画面動かしたい
	if (player->GetLocation().x >= 640 / 2 && player->GetPlayerState() == ePlayerState::MOVE)
	{
		//-45100
		Stage->SetVelocity(player->GetVelocity().x);
		if (Stage->GetVelocity().x <= -5100)
		{
			player->SetScrollEnd();
		}

		//クリボー用
		Kuribo->SetVelocity(player->GetVelocity().x);
		Nokonoko->SetVelocity(player->GetVelocity().x);
	}

	// 親クラスの更新処理を呼び出す
	return __super::Update(delta_second);
}

void InGameScene::Draw() const
{
	StageData* Stage = StageData::GetInstance();
	Stage->Load();

	//タイトルUIの描画
	DrawGraph(340, 10, mario_world, TRUE);
	DrawGraph(480, 10, mario_time, TRUE);
	DrawGraph(100, 10, mario_ui, TRUE);

	//コインの画像
	DrawGraph(190, 33, kakeru_ui[11], TRUE);     //コイン横の×
	DrawGraph(210, 34, coin_num_min[0], TRUE);   //コイン10の位の数字
	DrawGraph(230, 34, coin_num_sec[0], TRUE);   //コイン１の位の数字

	__super::Draw();

}

//終了処理
void InGameScene::Finalize()
{
	//親クラスの終了時処理を呼び出す
	__super::Finalize();
}

const eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::in_game;
}