#include "InGameScene.h"

#include "../Utility/ResourceManager.h"
#include "../Utility/InputManager.h"
#include "../Utility/StageData.h"


#include "../Objects/Mario/Player.h"
#include "../Objects/Enemy/kuribo.h"

#include "DxLib.h"
#include <fstream>



InGameScene::InGameScene()
	:player(nullptr)
	,Kuribo(nullptr)
	,velocity(0.0f)
	,fream_time(0.0f)
	,mario_time(0.0f)
	,mario_ui(0)
	,mario_world(0)
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
	//genelate_location = Vector2D(700.0f, 528.0f);

	//UIの読み込み
	mario_ui = rm->GetImages("Resource/images/UI/name_mario.png")[0];
	mario_time = rm->GetImages("Resource/images/UI/time.png")[0];
	mario_world = rm->GetImages("Resource/images/UI/world.png")[0];

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
	}




	////終盤画面スクロールを止める
	//if (scroll <= 1000)
	//{
	//	scroll = 1000;

	//	player->SetScrollEnd();
	//}


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
	return eSceneType ::in_game;
}

void InGameScene::CheckCollision(GameObjectBase* target, GameObjectBase* partner)
{
	// ヌルポチェック
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	// 当たり判定情報を取得
	RectCollision tc = target->GetCollision();
	RectCollision pc = partner->GetCollision();

	// **エラー対策: hit_object_type のサイズ確認**
	if (tc.hit_object_type.empty() || pc.hit_object_type.empty())
	{
		return; // 当たり判定対象が設定されていない場合、処理しない
	}

	// コリジョン対象のチェック
	if (!tc.IsCheckHitTarget(pc.object_type) && !pc.IsCheckHitTarget(tc.object_type))
	{
		return; // 互いに当たり判定対象でないならスキップ
	}

	// **座標を加算して、ワールド座標に変換**
	tc.top_left += target->GetLocation();
	tc.bottom_right += target->GetLocation();
	pc.top_left += partner->GetLocation();
	pc.bottom_right += partner->GetLocation();

	// **衝突判定を実行**
	if (IsCheckCollision(tc, pc))
	{
		// コリジョン発生時の処理
		target->OnHitCollision(partner);
		partner->OnHitCollision(target);
	}
}


