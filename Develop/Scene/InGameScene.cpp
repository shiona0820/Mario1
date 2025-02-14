#include "InGameScene.h"

#include "../Utility/ResourceManager.h"
#include "../Utility/InputManager.h"
#include "../Utility/StageData.h"


#include "../Objects/Mario/Player.h"
#include "../Objects/Enemy/kuribo.h"
<<<<<<< HEAD
#include "../HatenaBlock.h"
=======
#include "../Objects/Enemy/nokonoko.h"

#include "../coin.h"
>>>>>>> main

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
	// マップデータ読み込み生成処理
	LoadStageMapCSV();

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
<<<<<<< HEAD
	return eSceneType ::in_game;
}

/// <summary>
/// ステージマップ（壁）読み込み処理
/// </summary>
void InGameScene::LoadStageMapCSV()
{
	// 読み込むファイル名
	std::string file_name = "Resource/Map/StageMap.csv";
	// 指定ファイルを読み込む
	std::ifstream ifs(file_name);

	// エラーチェック
	if (ifs.fail())
	{
		throw (file_name + "が開けません\n");
	}

	// ファイルから1行ずつ読み込む
	std::string line;
	while (std::getline(ifs, line))
	{
		// 文字列を書式指定で分解して値を各変数に格納する
		char mode = NULL;		// 生成するオブジェクトモード
		int x_size = NULL;		// 生成する数（横）
		int y_size = NULL;		// 生成する数（縦）
		int spos_x = 0;			// 生成位置情報（横）
		int spos_y = 0;			// 生成位置情報（縦）
		sscanf_s(
			line.c_str(),
			"%c,%d,%d,%d,%d",
			&mode, (unsigned int)sizeof(mode),
			&x_size, &y_size,
			&spos_x, &spos_y
		);

		// モードによって、生成するオブジェクトを変える
		Vector2D generate_location;		// 生成位置の情報
		switch (mode)
		{
		case 'H':
			//ハテナブロック
			generate_location = (Vector2D((float)(spos_x - 1), (float)(spos_y - 1)) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			CreateObject<Hatena>(generate_location);
			break;

			//上記以外
		default:
			break;
		}
	}
}
=======
	return eSceneType::in_game;
}

//#ifdef D_PIVOT_CENTER
//
//
////当たり判定チェック処理（矩形の中心で当たり判定をとる）
//void InGameScene::HitCheckObject(GameObjectBase* a, GameObjectBase* b)
//{
//	//2つのオブジェクトの距離を取得
//	Vector2D diff = a->GetLocation() - b->GetLocation();
//
//	//2つのオブジェクトの当たり判定の大きさを取得
//	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;
//
//	//距離より大きさが大きい場合、Hit判定とする
//	if ((fabs(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
//	{
//		if (a->GetType() == b->GetType())
//		{
//			return;
//		}
//		else
//		{
//			//当たったことをオブジェクトに通知する
//			a->OnHitCollision(b);
//			b->OnHitCollision(a);
//		}
//	}
//}
//
//#else
//
////当たり判定チェック処理（左上頂点の座標から当たり判定計算を行う)
//void Scene::HitCheckObject(GameObjectBase* a, GameObjectBase* b)
//{
//	//右下頂点座標を取得する
//	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
//	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();
//
//	//矩形Aと矩形Bの位置関係を調べる
//	if ((a->GetLocation().x < b_lower_right.x) &&
//		(a->GetLocation().y < b_lower_right.y) &&
//		(a_lower_right.x > b->GetLocation().x) &&
//		(a_lower_right.y > b->GetLocation().y))
//	{
//		//オブジェクトにたいしてHit判定を通知する
//		a->OnHitCollision(b);
//		b->OnHitCollision(a);
//	}
//}
//#endif // D_PIVOT_CNETER
>>>>>>> main
