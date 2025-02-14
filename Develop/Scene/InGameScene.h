#pragma once
#define D_PIVOT_CENTER

#include "SceneBase.h"

class InGameScene : public SceneBase
{
private:
	class Player* player;		// プレイヤー情報
	class kuribo* Kuribo;      //クリボーの情報

	class coin* Coin;          //コインの情報
	std::vector<int> coin_animation;   //こいんのアニメーション
	//アニメーション用
	const int animation_num[4] = { 1,2,3,4 };
	int animation_count;
	float animation_time;

	std::vector<kuribo> enemies;      //複数描画用


	int back_ground_BGM;		// BGM
	
	float velocity;

	//タイトル画面UIの設定
	int mario_ui;
	int mario_world;
	int mario_time;

	int fream_time;   //フレームの時間設定

	std::vector<int> kakeru_ui;       //コイン横の×の画像
	std::vector<int>coin_num_min;         //コイン取得数の画像十の位
	std::vector<int>coin_num_sec;         //コイン取得数の画像一の位

public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Initialize() override;
	virtual eSceneType Update(const float& delta_second) override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	// 現在のシーンタイプ情報を取得する
	virtual const eSceneType GetNowSceneType() const override;

private:
	void AnimeCount(float delta_secound);


//private:
//
//	//当たり判定チェック処理
//	void HitCheckObject(GameObjectBase* a, GameObjectBase* b);
//
//	//オブジェクト生成処理
//	template <class T>
//	T* CreateObject(const Vector2D& location)
//	{
//		//指定したクラスを生成する
//		T* new_instance = new T();
//		//GameObjectクラスを継承しているか確認
//		GameObjectBase* new_object = dynamic_cast<GameObjectBase*>(new_instance);
//
//		//エラーチェック
//		if (new_object == nullptr)
//		{
//			delete new_instance;
//			throw ("ゲームオブジェクトが生成できませんでした");
//		}
//
//		//初期化処理
//		new_object->Initialize();
//		//位置情報の設定
//		new_object->SetLocation(location);
//
//		////オブジェクトリストに追加
//		//objects.push_back(new_object);
//
//		//インスタンスのポインタを返却
//		return new_instance;
//	}

};

